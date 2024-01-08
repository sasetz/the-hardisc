/*
   Copyright 2023 Ján Mach

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/

`include "settings.sv"
import p_hardisc::*;

module pipeline_5_ma (
    input logic s_clk_i[PROT_3REP],                 //clock signal
    input logic s_resetn_i[PROT_3REP],              //reset signal
    input logic[31:0] s_boot_add_i,                 //boot address

    input logic s_int_meip_i,                       //external interrupt
    input logic s_int_mtip_i,                       //timer interrupt
    input logic s_int_uce_i,                        //uncorrectable error in register-file
    input logic s_int_fcer_i,                       //fetch correctable error
`ifdef PROTECTED
    output logic[1:0] s_acm_settings_o,             //acm settings
    input logic s_exma_neq_i[PROT_3REP],            //discrepancy in result
`endif

    output logic s_stall_o[PROT_3REP],              //stall signal for lower stages
    output logic s_flush_o[PROT_3REP],              //flush signal for lower stages
    output logic s_hold_o[PROT_3REP],               //hold signal for lower stages 

    input logic[31:0] s_lsu_data_i,                 //LSU read data
    input logic s_lsu_ready_i[PROT_3REP],           //LSU ready
    input logic s_lsu_hresp_i[PROT_3REP],           //LSU bus error
    input logic s_lsu_busy_i[PROT_3REP],            //LSU cannot start new request

    input ictrl s_exma_ictrl_i[PROT_3REP],          //instruction control indicator
    input imiscon s_exma_imiscon_i[PROT_3REP],      //instruction misconduct indicator
    input f_part s_exma_f_i[PROT_3REP],             //instruction function
    input rf_add s_exma_rd_i[PROT_3REP],            //destination register address
    input logic[31:0] s_exma_val_i[PROT_3REP],      //result from EX stage
    input logic[11:0] s_exma_payload_i[PROT_3REP],  //instruction payload information    

    input logic[2:0] s_lsu_einfo_i[PROT_3REP],      //lsu error info
    input logic[31:0] s_lsu_fixed_data_i[PROT_3REP],//lsu fixed data

    input logic[30:0] s_bop_tadd_i,                 //predicted target address saved in the BOP
    input logic s_bop_pred_i,                       //the prediction is prepared in the BOP
    output logic s_bop_pop_o,                       //pop of the oldest entry in the BOP
    output logic s_ma_pred_clean_o,                 //clean selected prediction information
    output logic s_ma_pred_btbu_o,                  //update BTB of branch predictor
    output logic s_ma_pred_btrue_o,                 //executed branch has fulfilled condition
    output logic s_ma_pred_bpu_o,                   //update branch predictor
    output logic s_ma_pred_jpu_o,                   //update jump predictor

    output logic[31:0] s_ma_toc_addr_o[PROT_3REP],  //address for transfer of control
    output ictrl s_mawb_ictrl_o[PROT_3REP],         //instruction control indicator in WB stage
    output rf_add s_mawb_rd_o[PROT_3REP],           //destination register address in WB stage
    output logic[31:0] s_mawb_val_o[PROT_3REP],     //instruction result in WB stage
    output logic[31:0] s_rf_val_o[PROT_3REP],       //instruction result for register file
    output logic[31:0] s_read_data_o[PROT_3REP],    //direct access to read value
    
    output logic[31:0] s_rst_point_o[PROT_3REP],    //reset-point address
    output logic s_pred_disable_o,                  //disable any predictions
    output logic s_hrdmax_rst_o                     //max consecutive pipeline restarts reached
);

    logic s_flush_ma[PROT_3REP], s_stall_ma[PROT_3REP], s_lsu_stall[PROT_3REP];
    logic[31:0] s_write_val[PROT_3REP], s_lsurdata[PROT_3REP], s_int_trap[PROT_3REP], s_exc_trap[PROT_3REP], s_mepc[PROT_3REP], 
                s_ma_toc_addr[PROT_3REP], s_csr_val[PROT_3REP], s_bru_add[PROT_3REP], s_rst_point[PROT_3REP], 
                s_newrst_point[PROT_3REP], s_next_pc[PROT_3REP];
    logic[2:0] s_pc_incr[PROT_3REP];
    logic s_int_pending[PROT_3REP], s_exception[PROT_3REP], s_tereturn[PROT_3REP], s_ma_toc[PROT_3REP];
    logic s_bru_toc[PROT_3REP], s_rstpp[PROT_3REP], s_prior_rstpp[PROT_3REP], s_pred_bpu[PROT_3REP], s_pred_jpu[PROT_3REP], 
            s_ma_pred_btbu[PROT_3REP], s_ma_pred_btrue[PROT_3REP];
    logic s_interrupt[PROT_3REP], s_itaken[PROT_3REP];
    rf_add s_wmawb_rd[PROT_3REP], s_rmawb_rd[PROT_3REP], s_mawb_rd[PROT_3REP]; 
    logic[31:0] s_wmawb_val[PROT_3REP],s_rmawb_val[PROT_3REP],s_mawb_val[PROT_3REP];  
    ictrl s_wmawb_ictrl[PROT_3REP], s_rmawb_ictrl[PROT_3REP], s_mawb_ictrl[PROT_3REP];
    logic s_clk_prw[PROT_3REP], s_resetn_prw[PROT_3REP];
    ld_info s_wmawb_ldi[PROT_3REP], s_rmawb_ldi[PROT_3REP];
    logic s_int_lcer[PROT_3REP], s_nmi_luce[PROT_3REP], s_wb_error[PROT_3REP], s_wb_reset[PROT_3REP], s_ex_discrepancy[PROT_3REP], 
            s_ibus_rst_en[PROT_3REP], s_dbus_rst_en[PROT_3REP], s_berr_rst[PROT_3REP], s_trans_rst[PROT_3REP];
`ifdef PROTECTED_WITH_IFP
    logic[2:0] s_lsu_einfo[PROT_3REP];
    logic[1:0] s_wmawb_err[PROT_3REP], s_rmawb_err[PROT_3REP];
    logic[31:0] s_lsurdatac[PROT_3REP];
`endif

    assign s_mawb_rd_o      = s_mawb_rd;
    assign s_mawb_val_o     = s_mawb_val;
    assign s_mawb_ictrl_o   = s_mawb_ictrl;
    assign s_read_data_o    = s_rmawb_val;

    //Result value from the MA stage
    seu_regs #(.LABEL("MAWB_VAL"),.N(PROT_3REP))m_mawb_val (.s_c_i(s_clk_prw),.s_d_i(s_wmawb_val),.s_d_o(s_rmawb_val));
    //Destination register address
    seu_regs #(.LABEL("MAWB_RD"),.W($size(rf_add)),.N(PROT_3REP)) m_mawb_rd (.s_c_i(s_clk_prw),.s_d_i(s_wmawb_rd),.s_d_o(s_rmawb_rd));
    //Instruction control indicator
    seu_regs #(.LABEL("MAWB_ICTRL"),.W($size(ictrl)),.N(PROT_3REP)) m_mawb_ictrl (.s_c_i(s_clk_prw),.s_d_i(s_wmawb_ictrl),.s_d_o(s_rmawb_ictrl));
    //Load instruction information
    seu_regs #(.LABEL("MAWB_LDINFO"),.W($size(ld_info)),.N(PROT_3REP)) m_exma_ldinfo (.s_c_i(s_clk_prw),.s_d_i(s_wmawb_ldi),.s_d_o(s_rmawb_ldi));
`ifdef PROTECTED_WITH_IFP
    //Checksum for loaded value
    seu_regs #(.LABEL("MAWB_ERR"),.N(PROT_3REP),.W(2))m_mawb_err (.s_c_i(s_clk_prw),.s_d_i(s_wmawb_err),.s_d_o(s_rmawb_err));
`endif

`ifdef PROTECTED
    //Triple-Modular-Redundancy
    tmr_comb #(.W($size(rf_add))) m_tmr_mawb_rd (.s_d_i(s_rmawb_rd),.s_d_o(s_mawb_rd));
    tmr_comb #(.W($size(ictrl))) m_tmr_mawb_ictrl (.s_d_i(s_rmawb_ictrl),.s_d_o(s_mawb_ictrl));
`else
    assign s_mawb_rd        = s_rmawb_rd;
    assign s_mawb_ictrl     = s_rmawb_ictrl;
`endif

    //Reset-point output for lower stages
    assign s_rst_point_o        = s_rst_point;
    //Signals for the Predictor and Transfer of Control
    assign s_ma_toc_addr_o      = s_ma_toc_addr;
    assign s_bop_pop_o          = s_exma_ictrl_i[0][ICTRL_UNIT_BRU] & s_exma_payload_i[0][11];
    assign s_ma_pred_clean_o    = s_exma_imiscon_i[0] == IMISCON_DSCR;
    assign s_ma_pred_btbu_o     = s_ma_pred_btbu[0];
    assign s_ma_pred_btrue_o    = s_ma_pred_btrue[0];
    assign s_ma_pred_bpu_o      = s_pred_bpu[0] & ~s_exception[0] & ~s_rstpp[0];
    assign s_ma_pred_jpu_o      = s_pred_jpu[0] & ~s_exception[0] & ~s_rstpp[0];

    genvar i;
    generate
        for ( i = 0; i<PROT_3REP ; i++ ) begin : ma_replicator
            assign s_clk_prw[i]     = s_clk_i[i];
            assign s_resetn_prw[i]  = s_resetn_i[i];
`ifdef PROTECTED
            //Only two executors are present in the EX stage, if they were used, they results must be compared
            assign s_ex_discrepancy[i] =  s_exma_neq_i[i] & (
                                          s_exma_ictrl_i[i][ICTRL_UNIT_BRU] | 
                                          s_exma_ictrl_i[i][ICTRL_UNIT_ALU] | 
                                          s_exma_ictrl_i[i][ICTRL_UNIT_MDU]);
`else
            assign s_ex_discrepancy[i] = 1'b0;
`endif
            //Reset pipeline condition prior to MA stage
            assign s_prior_rstpp[i] = (s_exma_imiscon_i[i] == IMISCON_DSCR);
            //Reset pipeline on first occurence of bus error (if enabled in mhrdctrl0)
            assign s_trans_rst[i]   = (s_ibus_rst_en[i] & (s_exma_imiscon_i[i] == IMISCON_FERR)) | 
                                      (s_dbus_rst_en[i] & s_lsu_hresp_i[i] & s_exma_ictrl_i[i][ICTRL_UNIT_LSU]);
            //Reset pipeline if bus error occurred without previously intended transfer
            assign s_berr_rst[i]    = s_lsu_hresp_i[i] & ~s_exma_ictrl_i[i][ICTRL_UNIT_LSU];
            //Gathering pipeline reset informations
            assign s_rstpp[i]       = ~s_resetn_i[i] | s_prior_rstpp[i] | s_wb_reset[i] | s_trans_rst[i] | s_ex_discrepancy[i];

            //Branch/Jump unit
            bru m_bru
            (
                .s_active_i(s_exma_ictrl_i[i][ICTRL_UNIT_BRU]),
                .s_exma_f_i(s_exma_f_i[i]),
                .s_predicted_i(s_exma_payload_i[i][11]),
                .s_exma_val_i(s_exma_val_i[i]),
                .s_bop_tadd_i(s_bop_tadd_i),
                .s_bop_pred_i(s_bop_pred_i),

                .s_toc_o(s_bru_toc[i]),
                .s_branch_true_o(s_ma_pred_btrue[i]),
                .s_bp_update_o(s_pred_bpu[i]),
                .s_btb_update_o(s_ma_pred_btbu[i]),
                .s_jp_update_o(s_pred_jpu[i]),
                .s_itaken_o(s_itaken[i]),
                .s_target_add_o(s_bru_add[i])
            );

            //An address of the following instruction in the memory
            assign s_pc_incr[i]         = s_exma_ictrl_i[i][ICTRL_RVC] ? 3'd2 : 3'd4;
            fast_adder m_next_pc(.s_base_val_i(s_rst_point[i]),.s_add_val_i({13'd0,s_pc_incr[i]}),.s_val_o(s_next_pc[i])); 

            //Selection of the new reset point
            assign s_newrst_point[i]    = (s_interrupt[i]) ? s_int_trap[i] : 
                                          (s_exception[i]) ? s_exc_trap[i] : 
                                          (s_tereturn[i]) ? s_mepc[i] : 
                                          (s_itaken[i]) ? s_bru_add[i] : s_next_pc[i];

            //Transfer of control
            assign s_ma_toc_addr[i] = (s_rstpp[i] & ~s_interrupt[i]) ? s_rst_point[i] : s_newrst_point[i];
            assign s_ma_toc[i]      = (s_interrupt[i] | s_bru_toc[i] | s_exception[i] | s_tereturn[i] | s_rstpp[i]);

            //Interrupts - delay until LSU operation is finished
            assign s_interrupt[i]   = s_int_pending[i] & ~s_exma_ictrl_i[i][ICTRL_UNIT_LSU];

            //Stall if a data-bus transfer is extended
            assign s_lsu_stall[i]   = ~s_lsu_ready_i[i] | (s_lsu_busy_i[i] & s_exma_ictrl_i[i][ICTRL_UNIT_LSU]) ;
            assign s_stall_ma[i]    = s_lsu_stall[i];
            //Invalidate MA instruction if reset, interrupt, or exception is detected
            assign s_flush_ma[i]    = s_rstpp[i] | s_interrupt[i] | s_exception[i];

            //Stall lower stages on extended data-bus transfer
            assign s_stall_o[i]     = s_lsu_stall[i];
            //Flush lower stages on each TOC
            assign s_flush_o[i]     = s_ma_toc[i];
            //Hold signal - do not start new instruction in EX stage
            assign s_hold_o[i]      = s_int_pending[i] | s_wb_error[i] | s_lsu_busy_i[i];

            //Select result of the MA stage. NOTE: the REG_DEST bit in the instruction control must be active for register file write
            assign s_write_val[i]  = (s_exma_ictrl_i[i][ICTRL_UNIT_LSU]) ? s_lsu_data_i : 
                                     (s_exma_ictrl_i[i][ICTRL_UNIT_BRU]) ? s_next_pc[i] :
                                     (s_exma_ictrl_i[i][ICTRL_UNIT_CSR]) ? s_csr_val[i] : s_exma_val_i[i];

            always_comb begin : pipe_5_writer
                s_wmawb_val[i]  = s_write_val[i];
                if(s_flush_ma[i] | s_stall_ma[i])begin
                    s_wmawb_ictrl[i]= 7'b0;
                    s_wmawb_rd[i]   = 5'b0;
                    s_wmawb_ldi[i]  = 5'b0;
                end else begin
                    s_wmawb_ictrl[i]= s_exma_ictrl_i[i];
                    s_wmawb_rd[i]   = s_exma_rd_i[i];
                    s_wmawb_ldi[i]  = {s_exma_f_i[i][2:0], s_exma_val_i[i][1:0]};
                end
            end
        end

        /*  This section is part of WB stage  */
        for ( i = 0; i<PROT_3REP ; i++ ) begin : wb_replicator
            assign s_mawb_val[i] = (s_rmawb_ictrl[i][ICTRL_UNIT_LSU]) ? s_lsurdata[i] : s_rmawb_val[i];
            //Decoding of the loaded data, that can be forwarded to the lower stages
            lsu_decoder m_lsu_decoder(.s_lsu_data_i(s_rmawb_val[i]),.s_ld_info_i(s_rmawb_ldi[i]),.s_data_o(s_lsurdata[i]));
`ifdef PROTECTED_WITH_IFP
            //Decoding of the loaded data after potential fixing - long combinational path, data are not forwarded to the lower stages
            lsu_decoder m_lsu_decoder_slow(.s_lsu_data_i(s_lsu_fixed_data_i[i]),.s_ld_info_i(s_rmawb_ldi[i]),.s_data_o(s_lsurdatac[i])); 
            //Check LSU error information only if the WB-stage contains a LOAD instruction          
            assign s_lsu_einfo[i]= (s_rmawb_ictrl[i][ICTRL_UNIT_LSU] & s_rmawb_ictrl[i][ICTRL_REG_DEST]) ? s_lsu_einfo_i[i] : 3'b0;
            //Save error information for further processing
            assign s_wmawb_err[i]= s_flush_ma[i] ? 2'b0 : ({s_lsu_einfo[i][2],s_lsu_einfo[i][0]} | s_rmawb_err[i]); 
            //Any error in the WB stage prevents start of the new LSU transfer in the EX stage
            assign s_wb_error[i] = s_lsu_einfo[i][0] | s_rmawb_err[i][0];
            //WB error causes reset of the following instruction (except if the instruction is load/store)
            assign s_wb_reset[i] = s_wb_error[i] & ~s_exma_ictrl_i[i][ICTRL_UNIT_LSU];
            //Correctable error is a source of maskable interrupt
            assign s_int_lcer[i] = s_lsu_einfo[i][1];
            //Uncorrectable error is a source of not-maskable interrupt - preserve until the interrupt is taken
            assign s_nmi_luce[i] = s_lsu_einfo[i][2] | s_rmawb_err[i][1];
            //Data to be written into the register file - always take the data that has undergone a correction
            assign s_rf_val_o[i] = (s_rmawb_ictrl[i][ICTRL_UNIT_LSU]) ? s_lsurdatac[i] : s_rmawb_val[i];
`else
            assign s_wb_error[i] = 1'b0;
            assign s_wb_reset[i] = 1'b0;
            assign s_int_lcer[i] = 1'b0;
            assign s_nmi_luce[i] = 1'b0;
            //Data to be written into the register file
            assign s_rf_val_o[i] = s_mawb_val[i];
`endif
        end
        /*  End of WB stage  */ 
            
    endgenerate   

    csru m_csru
    (
        .s_clk_i(s_clk_i),
        .s_resetn_i(s_resetn_i),
        .s_boot_add_i(s_boot_add_i),
        .s_stall_i(s_stall_ma),
        .s_flush_i(s_flush_ma),
        .s_int_meip_i(s_int_meip_i),
        .s_int_mtip_i(s_int_mtip_i),
        .s_int_msip_i(1'b0),
        .s_int_uce_i(s_int_uce_i),
        .s_int_lcer_i(s_int_lcer),
        .s_int_fcer_i(s_int_fcer_i),
        .s_nmi_luce_i(s_nmi_luce),
        .s_hresp_i(s_lsu_hresp_i),
        .s_imiscon_i(s_exma_imiscon_i),
`ifdef PROTECTED
        .s_acm_settings_o(s_acm_settings_o),
`endif
        .s_rstpp_i(s_rstpp),
        .s_interrupted_i(s_interrupt),
        .s_newrst_point_i(s_newrst_point),
        .s_ictrl_i(s_exma_ictrl_i),
        .s_function_i(s_exma_f_i),
        .s_payload_i(s_exma_payload_i),
        .s_val_i(s_exma_val_i),
        .s_exc_trap_o(s_exc_trap), 
        .s_int_trap_o(s_int_trap), 
        .s_rst_point_o(s_rst_point),
        .s_csr_r_o(s_csr_val),
        .s_mepc_o(s_mepc),
        .s_treturn_o(s_tereturn),
        .s_int_pending_o(s_int_pending),
        .s_exception_o(s_exception),
        .s_ibus_rst_en_o(s_ibus_rst_en),
        .s_dbus_rst_en_o(s_dbus_rst_en),
        .s_pred_disable_o(s_pred_disable_o),
        .s_hrdmax_rst_o(s_hrdmax_rst_o)
    );

endmodule
