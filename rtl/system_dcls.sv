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

module system_dcls #(
    parameter PMA_REGIONS = 3,
    parameter DELAY_INPUTS = 0,
    parameter pma_cfg_t PMA_CFG[PMA_REGIONS-1:0] = PMA_DEFAULT
)(
    input logic s_clk_i[3],                 //clock signal
    input logic s_resetn_i[3],              //reset signal

    input logic s_int_meip_i,               //external interrupt
    input logic s_int_mtip_i,               //timer interrupt
    input logic[31:0] s_boot_add_i,         //boot address
    
    input logic[31:0] s_i_hrdata_i,         //AHB instruction bus - incomming read data
    input logic s_i_hready_i[3],            //AHB instruction bus - finish of transfer
    input logic s_i_hresp_i[3],             //AHB instruction bus - error response
    output logic[31:0] s_i_haddr_o,         //AHB instruction bus - request address
    output logic[31:0] s_i_hwdata_o,        //AHB instruction bus - request data to write
    output logic[2:0]s_i_hburst_o,          //AHB instruction bus - burst type indicator
    output logic s_i_hmastlock_o,           //AHB instruction bus - locked sequence indicator
    output logic[3:0]s_i_hprot_o,           //AHB instruction bus - protection control signals
    output logic[2:0]s_i_hsize_o,           //AHB instruction bus - size of the transfer
    output logic[1:0]s_i_htrans_o,          //AHB instruction bus - transfer type indicator
    output logic s_i_hwrite_o,              //AHB instruction bus - write indicator

    //custom AHB protection
    input logic[6:0] s_i_hrchecksum_i,      //AHB instruction bus - incoming checksum
    output logic[6:0] s_i_hwchecksum_o,     //AHB instruction bus - outgoing checksum
    output logic[5:0] s_i_hparity_o,        //AHB instruction bus - outgoing parity

    input logic[31:0] s_d_hrdata_i,         //AHB data bus - incomming read data
    input logic s_d_hready_i[3],            //AHB data bus - finish of transfer
    input logic s_d_hresp_i[3],             //AHB data bus - error response
    output logic[31:0] s_d_haddr_o,         //AHB data bus - request address
    output logic[31:0] s_d_hwdata_o,        //AHB data bus - request data to write
    output logic[2:0]s_d_hburst_o,          //AHB data bus - burst type indicator
    output logic s_d_hmastlock_o,           //AHB data bus - locked sequence indicator 
    output logic[3:0]s_d_hprot_o,           //AHB data bus - protection control signals
    output logic[2:0]s_d_hsize_o,           //AHB data bus - size of the transfer 
    output logic[1:0]s_d_htrans_o,          //AHB data bus - transfer type indicator
    output logic s_d_hwrite_o,              //AHB data bus - write indicator

    //custom AHB protection
    input logic[6:0] s_d_hrchecksum_i,      //AHB data bus - incoming checksum   
    output logic[6:0] s_d_hwchecksum_o,     //AHB data bus - outgoing checksum
    output logic[5:0] s_d_hparity_o,        //AHB data bus - outgoing parity

    output logic s_hrdmax_rst_o             //discrepancy between lockstepped cores
);

logic[5:0] s_i_hparity[2], s_d_hparity[2];
logic[6:0] s_i_hwchecksum[2], s_d_hwchecksum[2], s_i_hrchecksum[2], s_d_hrchecksum[2];
logic[31:0] s_i_haddr[2], s_i_hwdata[2], s_d_haddr[2], s_d_hwdata[2];
logic s_i_hwrite[2], s_i_hmastlock[2], s_d_hwrite[2], s_d_hmastlock[2], s_tmri_hready[3], s_tmri_hresp[3], s_tmrd_hready[3], s_tmrd_hresp[3];
logic[1:0] s_i_htrans[2], s_d_htrans[2];
logic[2:0] s_i_hsize[2], s_i_hburst[2], s_d_hsize[2], s_d_hburst[2];
logic[3:0] s_i_hprot[2], s_d_hprot[2];

logic[5:0] s_ribus_hparity[2][1];
logic[6:0] s_ribus_hrchecksum[2][1];
logic[31:0] s_ribus_haddr[2][1], s_ribus_hrdata[2][1];
logic s_ribus_hready[2][1], s_ribus_hresp[2][1];
logic[1:0] s_ribus_htrans[2][1];

logic[5:0] s_rdbus_hparity[2][1];
logic[6:0] s_rdbus_hwchecksum[2][1], s_rdbus_hrchecksum[2][1];
logic[31:0] s_rdbus_haddr[2][1], s_rdbus_hrdata[2][1], s_rdbus_hwdata[2][1];
logic s_rdbus_hwrite[2][1], s_rdbus_hready[2][1], s_rdbus_hresp[2][1];
logic[1:0] s_rdbus_htrans[2][1];
logic[2:0] s_rdbus_hsize[2][1];

logic s_hrdmax_rst[2], s_i_discrepancy[3], s_d_discrepancy[3], s_wdiscrepancy[3], s_rdiscrepancy[3], s_tmr_discrepancy[1],
      s_wdbus_dphase[3], s_rdbus_dphase[3], s_resetn[2][1], s_int_meip[2][1], s_int_mtip[2][1];

seu_ff_rst #(.LABEL("DISCREPANCY"),.W(1),.N(3)) m_discr (.s_c_i(s_clk_i),.s_r_i(s_resetn_i),.s_d_i(s_wdiscrepancy),.s_q_o(s_rdiscrepancy));
seu_ff_rst #(.LABEL("DBUS_DPHASE"),.W(1),.N(3)) m_dbusd (.s_c_i(s_clk_i),.s_r_i(s_resetn_i),.s_d_i(s_wdbus_dphase),.s_q_o(s_rdbus_dphase));

tmr_comb #(.OUT_REPS(1),.W(1)) m_tmr_discrepancy (.s_d_i(s_rdiscrepancy),.s_d_o(s_tmr_discrepancy));

assign s_hrdmax_rst_o   = s_tmr_discrepancy[0];

assign s_i_htrans_o     = s_i_htrans[0];
assign s_i_haddr_o      = s_i_haddr[0];
assign s_i_hwdata_o     = 32'b0;
assign s_i_hburst_o     = 3'b0;
assign s_i_hmastlock_o  = 1'b0;
assign s_i_hprot_o      = 4'b0;
assign s_i_hsize_o      = 3'b010;
assign s_i_hwrite_o     = 1'b0;
assign s_i_hparity_o    = s_i_hparity[0];
assign s_i_hwchecksum_o = 7'b0;

assign s_d_htrans_o     = s_d_htrans[0];
assign s_d_haddr_o      = s_d_haddr[0];
assign s_d_hwdata_o     = s_d_hwdata[0];
assign s_d_hburst_o     = 3'b0;
assign s_d_hmastlock_o  = 1'b0;
assign s_d_hprot_o      = 4'b0;
assign s_d_hsize_o      = s_d_hsize[0];
assign s_d_hwrite_o     = s_d_hwrite[0];
assign s_d_hparity_o    = s_d_hparity[0];
assign s_d_hwchecksum_o = s_d_hwchecksum[0];

/* Instruction interface */
assign s_ribus_hparity[1][0]    = s_i_hparity[1];
assign s_ribus_haddr[1][0]      = s_i_haddr[1];
assign s_ribus_htrans[1][0]     = s_i_htrans[1];
//Response
tmr_comb #(.OUT_REPS(3),.W(1))  m_tmr_i_hready (.s_d_i(s_i_hready_i),.s_d_o(s_tmri_hready));
tmr_comb #(.OUT_REPS(3),.W(1))  m_tmr_i_hresp (.s_d_i(s_i_hresp_i),.s_d_o(s_tmri_hresp));
assign s_ribus_hready[0][0]     = s_tmri_hready[0];
assign s_ribus_hresp[0][0]      = s_tmri_hresp[0];
assign s_ribus_hrdata[0][0]     = s_i_hrdata_i;
assign s_ribus_hrchecksum[0][0] = s_i_hrchecksum_i;

/* Data interface */
assign s_rdbus_hparity[1][0]    = s_d_hparity[1];
assign s_rdbus_haddr[1][0]      = s_d_haddr[1];
assign s_rdbus_htrans[1][0]     = s_d_htrans[1];
assign s_rdbus_hwchecksum[1][0] = s_d_hwchecksum[1];
assign s_rdbus_hwdata[1][0]     = s_d_hwdata[1];
assign s_rdbus_hwrite[1][0]     = s_d_hwrite[1];
assign s_rdbus_hsize[1][0]      = s_d_hsize[1];
//Response
tmr_comb #(.OUT_REPS(3),.W(1))  m_tmr_d_hready (.s_d_i(s_d_hready_i),.s_d_o(s_tmrd_hready));
tmr_comb #(.OUT_REPS(3),.W(1))  m_tmr_d_hresp (.s_d_i(s_d_hresp_i),.s_d_o(s_tmrd_hresp));
assign s_rdbus_hready[0][0]     = s_tmrd_hready[0];
assign s_rdbus_hresp[0][0]      = s_tmrd_hresp[0];
assign s_rdbus_hrdata[0][0]     = s_d_hrdata_i;
assign s_rdbus_hrchecksum[0][0] = s_d_hrchecksum_i;

//Other inputs
assign s_resetn[0][0]   = s_resetn_i[0];
assign s_int_meip[0][0] = s_int_meip_i;
assign s_int_mtip[0][0] = s_int_mtip_i;

genvar i;
generate
    if(DELAY_INPUTS == 1)begin
        /* Instruction interface */
        //Save request of leading core for comparison in the next clock cycle 
        seu_ff #(.LABEL("IBUS_HPARITY"),.W(6),.N(1))    m_i_hparity (.s_c_i({s_clk_i[0]}),.s_d_i({s_i_hparity[0]}),.s_q_o(s_ribus_hparity[0]));
        seu_ff #(.LABEL("IBUS_HADDR"),.W(32),.N(1))     m_i_haddr (.s_c_i({s_clk_i[0]}),.s_d_i({s_i_haddr[0]}),.s_q_o(s_ribus_haddr[0]));
        seu_ff #(.LABEL("IBUS_HTRANS"),.W(2),.N(1))     m_i_htrans (.s_c_i({s_clk_i[0]}),.s_d_i({s_i_htrans[0]}),.s_q_o(s_ribus_htrans[0]));
        //Save response for the trailing core
        seu_ff #(.LABEL("IBUS_HREADY"),.W(1),.N(1))     m_i_hready (.s_c_i({s_clk_i[1]}),.s_d_i({s_tmri_hready[1]}),.s_q_o(s_ribus_hready[1]));
        seu_ff #(.LABEL("IBUS_HRESP"),.W(1),.N(1))      m_i_hresp (.s_c_i({s_clk_i[1]}),.s_d_i({s_tmri_hresp[1]}),.s_q_o(s_ribus_hresp[1]));
        seu_ff #(.LABEL("IBUS_HRDATA"),.W(32),.N(1))    m_i_hrdata (.s_c_i({s_clk_i[1]}),.s_d_i({s_i_hrdata_i}),.s_q_o(s_ribus_hrdata[1]));
        seu_ff #(.LABEL("IBUS_HRCHECKSUM"),.W(7),.N(1)) m_i_hrchecksum (.s_c_i({s_clk_i[1]}),.s_d_i({s_i_hrchecksum_i}),.s_q_o(s_ribus_hrchecksum[1]));

        /* Data interface */
        //Save request of leading core for comparison in the next clock cycle 
        seu_ff #(.LABEL("DBUS_HPARITY"),.W(6),.N(1))    m_d_hparity (.s_c_i({s_clk_i[0]}),.s_d_i({s_d_hparity[0]}),.s_q_o(s_rdbus_hparity[0]));
        seu_ff #(.LABEL("DBUS_HADDR"),.W(32),.N(1))     m_d_haddr (.s_c_i({s_clk_i[0]}),.s_d_i({s_d_haddr[0]}),.s_q_o(s_rdbus_haddr[0]));
        seu_ff #(.LABEL("DBUS_HTRANS"),.W(2),.N(1))     m_d_htrans (.s_c_i({s_clk_i[0]}),.s_d_i({s_d_htrans[0]}),.s_q_o(s_rdbus_htrans[0]));
        seu_ff #(.LABEL("DBUS_HWCHECKSUM"),.W(7),.N(1)) m_d_hwchecksum (.s_c_i({s_clk_i[0]}),.s_d_i({s_d_hwchecksum[0]}),.s_q_o(s_rdbus_hwchecksum[0]));
        seu_ff #(.LABEL("DBUS_HWDATA"),.W(32),.N(1))    m_d_hwdata (.s_c_i({s_clk_i[0]}),.s_d_i({s_d_hwdata[0]}),.s_q_o(s_rdbus_hwdata[0]));
        seu_ff #(.LABEL("DBUS_HWRITE"),.W(1),.N(1))     m_d_hwrite (.s_c_i({s_clk_i[0]}),.s_d_i({s_d_hwrite[0]}),.s_q_o(s_rdbus_hwrite[0]));
        seu_ff #(.LABEL("DBUS_HSIZE"),.W(3),.N(1))      m_d_hsize (.s_c_i({s_clk_i[0]}),.s_d_i({s_d_hsize[0]}),.s_q_o(s_rdbus_hsize[0]));
        //Save response for the trailing core
        seu_ff #(.LABEL("DBUS_HREADY"),.W(1),.N(1))     m_d_hready (.s_c_i({s_clk_i[1]}),.s_d_i({s_tmrd_hready[1]}),.s_q_o(s_rdbus_hready[1]));
        seu_ff #(.LABEL("DBUS_HRESP"),.W(1),.N(1))      m_d_hresp (.s_c_i({s_clk_i[1]}),.s_d_i({s_tmrd_hresp[1]}),.s_q_o(s_rdbus_hresp[1]));
        seu_ff #(.LABEL("DBUS_HRDATA"),.W(32),.N(1))    m_d_hrdata (.s_c_i({s_clk_i[1]}),.s_d_i({s_d_hrdata_i}),.s_q_o(s_rdbus_hrdata[1]));
        seu_ff #(.LABEL("DBUS_HRCHECKSUM"),.W(7),.N(1)) m_d_hrchecksum (.s_c_i({s_clk_i[1]}),.s_d_i({s_d_hrchecksum_i}),.s_q_o(s_rdbus_hrchecksum[1]));
        
        //Other inputs
        seu_ff #(.LABEL("RESET"),.W(1),.N(1))   m_reset (.s_c_i({s_clk_i[1]}),.s_d_i({s_resetn_i[1]}),.s_q_o(s_resetn[1]));
        seu_ff #(.LABEL("MEIP"),.W(1),.N(1))    m_meip (.s_c_i({s_clk_i[1]}),.s_d_i({s_int_meip_i}),.s_q_o(s_int_meip[1]));
        seu_ff #(.LABEL("MTIP"),.W(1),.N(1))    m_mtip (.s_c_i({s_clk_i[1]}),.s_d_i({s_int_mtip_i}),.s_q_o(s_int_mtip[1]));
    end else begin
        /* Instruction interface */
        assign s_ribus_hparity[0][0]    = s_i_hparity[0];
        assign s_ribus_haddr[0][0]      = s_i_haddr[0];
        assign s_ribus_htrans[0][0]     = s_i_htrans[0];
        //Response
        assign s_ribus_hready[1][0]     = s_tmri_hready[1];
        assign s_ribus_hresp[1][0]      = s_tmri_hresp[1];
        assign s_ribus_hrdata[1][0]     = s_i_hrdata_i;
        assign s_ribus_hrchecksum[1][0] = s_i_hrchecksum_i;

        /* Data interface */
        assign s_rdbus_hparity[0][0]    = s_d_hparity[0];
        assign s_rdbus_haddr[0][0]      = s_d_haddr[0];
        assign s_rdbus_htrans[0][0]     = s_d_htrans[0];
        assign s_rdbus_hwchecksum[0][0] = s_d_hwchecksum[0];
        assign s_rdbus_hwdata[0][0]     = s_d_hwdata[0];
        assign s_rdbus_hwrite[0][0]     = s_d_hwrite[0];
        assign s_rdbus_hsize[0][0]      = s_d_hsize[0];
        //Response
        assign s_rdbus_hready[1][0]     = s_tmrd_hready[1];
        assign s_rdbus_hresp[1][0]      = s_tmrd_hresp[1];
        assign s_rdbus_hrdata[1][0]     = s_d_hrdata_i;
        assign s_rdbus_hrchecksum[1][0] = s_d_hrchecksum_i;

        //Other inputs
        assign s_resetn[1][0]       = s_resetn_i[1];
        assign s_int_meip[1][0]     = s_int_meip_i;
        assign s_int_mtip[1][0]     = s_int_mtip_i;
    end
    for (i = 0; i < 2;i++ ) begin : rep
        hardisc #(.PMA_REGIONS(PMA_REGIONS),.PMA_CFG(PMA_CFG)) core
        (
            .s_clk_i({s_clk_i[i]}),
            .s_resetn_i({s_resetn[i][0]}),
            .s_int_meip_i(s_int_meip[i][0]),
            .s_int_mtip_i(s_int_mtip[i][0]),
            .s_boot_add_i(s_boot_add_i),
            
            .s_i_hrdata_i(s_ribus_hrdata[i][0]),
            .s_i_hready_i(s_ribus_hready[i]),
            .s_i_hresp_i(s_ribus_hresp[i]),
            .s_i_haddr_o(s_i_haddr[i]),
            .s_i_hwdata_o(s_i_hwdata[i]),
            .s_i_hburst_o(s_i_hburst[i]),
            .s_i_hmastlock_o(s_i_hmastlock[i]),
            .s_i_hprot_o(s_i_hprot[i]),
            .s_i_hsize_o(s_i_hsize[i]),
            .s_i_htrans_o(s_i_htrans[i]),
            .s_i_hwrite_o(s_i_hwrite[i]),

            .s_i_hrchecksum_i(s_ribus_hrchecksum[i][0]),
            .s_i_hwchecksum_o(s_i_hwchecksum[i]),
            .s_i_hparity_o(s_i_hparity[i]),

            .s_d_hrdata_i(s_rdbus_hrdata[i][0]),
            .s_d_hready_i(s_rdbus_hready[i]),
            .s_d_hresp_i(s_rdbus_hresp[i]),
            .s_d_haddr_o(s_d_haddr[i]),
            .s_d_hwdata_o(s_d_hwdata[i]),
            .s_d_hburst_o(s_d_hburst[i]),
            .s_d_hmastlock_o(s_d_hmastlock[i]),
            .s_d_hprot_o(s_d_hprot[i]),
            .s_d_hsize_o(s_d_hsize[i]),
            .s_d_htrans_o(s_d_htrans[i]),
            .s_d_hwrite_o(s_d_hwrite[i]),

            .s_d_hrchecksum_i(s_rdbus_hrchecksum[i][0]),
            .s_d_hwchecksum_o(s_d_hwchecksum[i]),
            .s_d_hparity_o(s_d_hparity[i]),

            .s_hrdmax_rst_o(s_hrdmax_rst[i])
        );        
    end
    for (i = 0; i < 3;i++ ) begin : checker_rep
        always_comb begin
            s_i_discrepancy[i] = 1'b0;
            if(s_ribus_htrans[0][0] != s_ribus_htrans[1][0])begin
                s_i_discrepancy[i] = 1'b1;
            end else begin
                if(s_ribus_htrans[i%2][0] != 2'b00)begin
                    s_i_discrepancy[i] =(s_ribus_hparity[0][0]  != s_ribus_hparity[1][0]) |
                                        (s_ribus_haddr[0][0]    != s_ribus_haddr[1][0]);
                end
            end
        end
        always_comb begin
            s_d_discrepancy[i] = 1'b0;
            if(s_rdbus_htrans[0][0] != s_rdbus_htrans[1][0])begin
                s_d_discrepancy[i] = 1'b1;
            end else begin
                s_d_discrepancy[i] = ((s_rdbus_htrans[i%2][0] != 2'b00) && ((s_rdbus_haddr[0][0] != s_rdbus_haddr[1][0]) || 
                                                                          (s_rdbus_hsize[0][0] != s_rdbus_hsize[1][0]) ||
                                                                          (s_rdbus_hwrite[0][0]!= s_rdbus_hwrite[1][0]) || 
                                                                          (s_rdbus_hparity[0][0] != s_rdbus_hparity[1][0]))) ||
                                     ((s_rdbus_dphase[i] != 1'b0) && ((s_rdbus_hwdata[0][0] != s_rdbus_hwdata[1][0]) || 
                                                                      (s_rdbus_hwchecksum[0][0]  != s_rdbus_hwchecksum[1][0])));                            
            end
            s_wdbus_dphase[i] = s_tmrd_hready[i] ? ((s_rdbus_htrans[i%2][0] == 2'b10) & s_rdbus_hwrite[i%2][0]) : s_rdbus_dphase[i];
        end
        always_comb begin
            if(s_tmr_discrepancy[0])begin
                s_wdiscrepancy[i] = 1'b1;
            end else begin
                s_wdiscrepancy[i] = s_i_discrepancy[i] | s_d_discrepancy[i];
            end      
        end
    end
endgenerate


endmodule