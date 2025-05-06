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

module decoder (
    input logic[2:0] s_fetch_error_i,   //error during instruction fetch
    input logic s_align_error_i,        //error during instruction aligning
    input logic[31:0] s_instr_i,    //aligned instruction
    input logic s_prediction_i,     //indicates prediction made from the instruction

    output logic[20:0] s_payload_o, //payload information of the instruction
    output f_part s_f_o,            //specify instruction function
    output rf_add s_rs1_o,          //read address for read port 1 of register file
    output rf_add s_rs2_o,          //read address for read port 2 of register file
    output rf_add s_rd_o,           //write addres for register file
    output sctrl s_sctrl_o,         //source control indicator
    output ictrl s_ictrl_o,         //instruction control indicator
    output imiscon s_imiscon_o      //instruction misconduct indicator 
);
    logic s_load, s_store, s_branch, s_jalr, s_jal, s_op, s_op_imm, s_lui, s_system, s_auipc, s_fence, s_srla, s_add, s_m_op; 
    logic s_csr_need_rs1, s_sub_sra, s_ecb, s_mret, s_csr, s_illegal;

    logic s_b_binvbclr, s_b_shadd, s_b_bsetbext, s_b_minmax, s_b_clmul, s_b_ror, s_b_rol, s_b_gates;
    logic s_b_sextb, s_b_sexth, s_b_zexth, s_b_rev8, s_b_orcb, s_b_clz, s_b_cpop, s_b_ctz;
    logic s_b_is_min, s_b_misc, s_b_op, s_b_op_imm;
    logic s_b_primary, s_b_secondary, s_b_tertiary;
    logic[6:0] s_b_opcode;

    logic[1:0] s_csr_fun;
    logic[2:0] s_brj_f;
    logic[19:0] s_imm, s_c_imm, s_imm_lui_auipc, s_imm_jal, s_imm_ls_i_jalr, s_imm_branch, s_imm_csr;
    opcode s_opcode;
    f_part s_i_f, s_c_f;
    rf_add s_rd, s_rs1, s_rs2, s_c_rd, s_c_rs1, s_c_rs2;
    sctrl s_src_ctrl, s_c_src_ctrl;
    ictrl s_instr_ctrl, s_c_instr_ctrl;
    imiscon s_instr_miscon, s_c_instr_miscon, s_dec_imiscon;
    logic s_rvc, s_alter, s_base, s_known;
    logic[4:0] s_csr_add;
    logic[3:0] s_csr_type;
    logic s_pred_not_allowed;

    //Selection of outputs depends on the instruction type (RVC or RVI)
    assign s_rvc        = s_instr_i[1:0] != 2'b11;
    assign s_rd_o       = (s_rvc) ? s_c_rd : s_rd;
    assign s_rs1_o      = (s_rvc) ? s_c_rs1 : s_rs1;
    assign s_rs2_o      = (s_rvc) ? s_c_rs2 : s_rs2;
    assign s_f_o        = (s_rvc) ? s_c_f : s_i_f;
    assign s_sctrl_o    = (s_rvc) ? s_c_src_ctrl : s_src_ctrl;
    assign s_ictrl_o    = (s_imiscon_o != IMISCON_FREE) ?
                          {s_align_error_i | s_rvc, 7'b0000000} : //The RVC means the Predictor will not increment address before invalidiation
                          (s_rvc) ? s_c_instr_ctrl : s_instr_ctrl;
    assign s_imiscon_o  = (s_align_error_i) ? IMISCON_DSCR : //Restart due to wrong alignment, probably caused by the Predictor
                          ((s_fetch_error_i != FETCH_VALID) & (s_fetch_error_i != FETCH_INCER)) ? s_fetch_error_i : s_dec_imiscon;
    assign s_dec_imiscon = (s_rvc) ? s_c_instr_miscon : s_instr_miscon;

    //Payload information - leveraged by upper stages
    assign s_payload_o[20]  = s_prediction_i;
    assign s_payload_o[19:0]= (s_b_misc) ? {8'b0, s_instr_i[31:20]} : (s_rvc) ? s_c_imm : (s_fence) ? (20'h2) : s_imm;

    //RVC decoder
    c_decoder m_cdecoder
    (
        .s_instr_i(s_instr_i[15:0]),
        .s_prediction_i(s_prediction_i),
        .s_imm_o(s_c_imm),
        .s_f_o(s_c_f),
        .s_rs1_o(s_c_rs1),
        .s_rs2_o(s_c_rs2),
        .s_rd_o(s_c_rd),
        .s_sctrl_o(s_c_src_ctrl),
        .s_ictrl_o(s_c_instr_ctrl),
        .s_imiscon_o(s_c_instr_miscon)
    );

    /**************** RVI decoder **************/

    assign s_base       = s_instr_i[31:25] == 7'b0000000;
    assign s_alter      = s_instr_i[31:25] == 7'b0100000;
    assign s_rd         = s_instr_i[11:7];
    assign s_rs1        = s_instr_i[19:15];
    assign s_rs2        = s_instr_i[24:20];
    assign s_opcode     = s_instr_i[6:2];

    assign s_b_op       = s_opcode == OPC_OP;
    assign s_b_op_imm   = s_opcode == OPC_OP_IMM;
    assign s_b_opcode   = s_instr_i[31:25];
    
    //Instruction group analyzer
    assign s_load 		= (s_opcode == OPC_LOAD) & s_instr_i[14:12] != 3'b011 & s_instr_i[14:12] != 3'b111 & s_instr_i[14:12] != 3'b110;
	assign s_store 	    = (s_opcode == OPC_STORE) & (s_instr_i[14:12] == 3'b000 | s_instr_i[14:12] == 3'b001 | s_instr_i[14:12] == 3'b010);
	assign s_branch 	= (s_opcode == OPC_BRANCH) & s_instr_i[14:12] != 3'b011 & s_instr_i[14:12] != 3'b010;
	assign s_jalr 		= (s_opcode == OPC_JALR) & s_instr_i[14:12] == 3'b000;
	assign s_jal 		= (s_opcode == OPC_JAL);
	assign s_op 		= (s_opcode == OPC_OP) & ((s_instr_i[14:12] == 3'b101 & (s_base | s_alter | s_m_op)) || 
                                                  (s_instr_i[14:12] == 3'b000 & (s_base | s_alter | s_m_op)) || 
                                                  (s_instr_i[14:12] != 3'b101 & s_instr_i[14:12] != 3'b000 & (s_base | s_m_op)));
	assign s_op_imm 	= (s_opcode == OPC_OP_IMM) & ((s_instr_i[14:12] == 3'b001 & s_base) || 
                                                      (s_instr_i[14:12] == 3'b101 & (s_base | s_alter)) || 
                                                      (s_instr_i[14:12] != 3'b101 & s_instr_i[14:12] != 3'b001));
    assign s_sub_sra    = s_instr_i[30] & (((s_op & ~s_m_op) & s_add) | ((s_op_imm | (s_op & ~s_m_op)) & s_srla));
	assign s_lui        = (s_opcode == OPC_LUI);
	assign s_system 	= (s_opcode == OPC_SYSTEM);
	assign s_auipc      = (s_opcode == OPC_AUIPC);
	assign s_fence 	    = (s_opcode == OPC_FENCE) & (s_instr_i[14:12] == 3'b000 | s_instr_i[14:12] == 3'b001);

    // Bit extension group analyzer
    // 2+ instructions per group
    assign s_b_binvbclr = (s_b_op || s_b_op_imm) &
                          (s_b_opcode == BE_GROUP_BINV || s_b_opcode == BE_GROUP_BCLR) &
                          (s_instr_i[14:12] == 3'b001);
    assign s_b_shadd    = s_b_op &
                          s_b_opcode == BE_GROUP_SHADD &
                          s_instr_i[14:12] != 3'b000 & s_instr_i[12] == 1'b0;
    assign s_b_bsetbext = (s_b_op || s_b_op_imm) &
                          ((s_instr_i[14:12] == 3'b001 & s_b_opcode == BE_GROUP_BSET) |
                          (s_instr_i[14:12] == 3'b101 & s_b_opcode == BE_GROUP_BEXT));
    assign s_b_minmax   = s_b_op &
                          s_b_opcode == BE_GROUP_MINMAX &
                          s_instr_i[14] == 1'b1;
    assign s_b_clmul    = s_b_op &
                          s_b_opcode == BE_GROUP_CLMUL &
                          s_instr_i[14:12] != 3'b000 & s_instr_i[14] == 1'b0;
    assign s_b_ror      = (s_b_op || s_b_op_imm) &
                          (s_b_opcode == BE_GROUP_ROT) &
                          (s_instr_i[14:12] == 3'b101);
    assign s_b_rol      = s_b_op &
                          s_b_opcode == BE_GROUP_ROT &
                          s_instr_i[14:12] == 3'b001;
    assign s_b_gates    = s_b_op &
                          s_b_opcode == BE_GROUP_GATES &
                          s_instr_i[14:12] != 3'b101 & s_instr_i[14] == 1'b1;

    // one instruction per group
    assign s_b_sextb    = s_b_op_imm &
                          s_instr_i[31:20] == BEU_I_SEXTB &
                          s_instr_i[14:12] == 3'b001;
    assign s_b_sexth    = s_b_op_imm &
                          s_instr_i[31:20] == BEU_I_SEXTH &
                          s_instr_i[14:12] == 3'b001;
    assign s_b_zexth    = s_b_op &
                          s_instr_i[31:20] == BEU_I_ZEXTH &
                          s_instr_i[14:12] == 3'b100;
    assign s_b_rev8     = s_b_op_imm &
                          s_instr_i[31:20] == BEU_I_REV8 &
                          s_instr_i[14:12] == 3'b101;
    assign s_b_orcb     = s_b_op_imm &
                          s_instr_i[31:20] == BEU_I_ORCB &
                          s_instr_i[14:12] == 3'b101;
    assign s_b_clz      = s_b_op_imm &
                          s_instr_i[31:20] == BEU_I_CLZ &
                          s_instr_i[14:12] == 3'b001;
    assign s_b_cpop     = s_b_op_imm &
                          s_instr_i[31:20] == BEU_I_CPOP &
                          s_instr_i[14:12] == 3'b001;
    assign s_b_ctz      = s_b_op_imm &
                          s_instr_i[31:20] == BEU_I_CTZ &
                          s_instr_i[14:12] == 3'b001;

    assign s_known      = (s_load | s_store | s_branch | s_jalr | s_jal | s_op | s_op_imm | s_lui | s_auipc | s_fence | s_csr | s_mret | s_ecb |
                           s_b_binvbclr | s_b_shadd | s_b_bsetbext | s_b_minmax | s_b_clmul | s_b_ror | s_b_rol | s_b_gates |
                           s_b_sextb | s_b_sexth | s_b_zexth | s_b_rev8 | s_b_orcb | s_b_clz | s_b_cpop | s_b_ctz);
    assign s_illegal    = (~s_known) | (s_csr & (s_csr_add == 5'b11111));

    //Auxiliary values
    assign s_m_op       = (s_instr_i[31:25] == 7'b1);
    assign s_srla       = (s_instr_i[14:12] == 3'b101);
    assign s_add        = (s_instr_i[14:12] == 3'b000);
    assign s_ecb        = s_system & ~((|s_instr_i[31:21]) | (|s_instr_i[19:7]));
    assign s_mret       = s_system & s_instr_i[31:25] == 7'b0011000 & s_instr_i[24:20] == 5'b00010 & ~(|s_instr_i[19:7]);
    assign s_csr        = s_system & s_instr_i[14:12] != 3'b000;
    assign s_b_is_min   = (s_instr_i[14:13] == 2'b10);
    assign s_b_misc  = (s_b_sextb | s_b_sexth | s_b_zexth | s_b_rev8 | s_b_orcb | s_b_clz | s_b_cpop | s_b_ctz);
    assign s_b_primary  = (s_b_shadd | s_b_bsetbext | s_b_ror | s_b_rol | s_b_gates);
    assign s_b_secondary= s_b_binvbclr;
    assign s_b_tertiary = (s_b_clmul | s_b_minmax | s_b_misc);
    
    //Immediate value, note that if LSB is defined to be 1'b0, it is not propagated from the ID stage
    assign s_imm_lui_auipc  = {s_instr_i[31:12]}; //lui, auipc
    assign s_imm_jal        = {s_instr_i[31],s_instr_i[19:12],s_instr_i[20],s_instr_i[30:21]}; //jal
    assign s_imm_branch     = {{9{s_instr_i[31]}},s_instr_i[7],s_instr_i[30:25],s_instr_i[11:8]}; //branches
    assign s_imm_ls_i_jalr  = {{9{s_instr_i[31]}},s_instr_i[30:25],(s_store)?s_instr_i[11:7]:s_instr_i[24:20]}; //ls_imm_jalr
    assign s_imm_csr        = {4'b0,s_rs1,s_csr_fun,s_csr_type,s_csr_add}; //csr
    assign s_imm            =   (s_system) ? s_imm_csr :
                                (s_jal) ? s_imm_jal : 
                                (s_lui | s_auipc) ? s_imm_lui_auipc : 
                                (s_branch) ? s_imm_branch : s_imm_ls_i_jalr;
    //Instruction function
    assign s_brj_f      =   (s_jal | s_jalr | s_fence) ? (s_jalr ? 3'b011 : 3'b100) :
                            (s_instr_i[13:12] == 2'b00 ) ? 3'b010 :
                            (s_instr_i[14:12] == 3'b101) ? 3'b110 :
                            (s_instr_i[14:12] == 3'b110) ? 3'b011 : s_instr_i[14:12];
    assign s_i_f[3]     = (s_jalr | s_jal | s_fence | s_auipc | s_sub_sra | s_store | (s_branch & s_instr_i[14:12] != 3'b110 & s_instr_i[14:12] != 3'b100) |
                          s_b_shadd | s_b_bsetbext | s_b_clmul | (s_b_is_min & s_b_minmax) | s_b_misc);
    assign s_i_f[2:0]   = (s_b_primary)   ? s_instr_i[14:12] :
                          (s_b_secondary) ? s_instr_i[31:29] :
                          (s_b_tertiary)  ? (
                              s_b_misc    ? BEU_MISC[2:0] :
                              s_b_minmax  ? {s_b_is_min, 1'b1, s_instr_i[12]} :
                              s_b_clmul ? (
                                  s_instr_i[13:12] == 2'b01 ? 3'd0 : // BEU_MDU_CLMUL
                                  s_instr_i[13:12] == 2'b11 ? 3'd1 : // BEU_MDU_CLMULH
                                                              3'd2   // BEU_MDU_CLMULR
                                  ) : 3'bxxx // FIXME: for debugging purposes
                              ) :
                          (s_instr_ctrl[ICTRL_UNIT_BRU]) ? s_brj_f: (s_lui | s_auipc) ? ((s_auipc) ? 3'b100 : 3'b000) : s_instr_i[14:12];

    //CSR address compressor
    always_comb begin : machine_csr_address
        case (s_instr_i[31:20])
            CSR_MSTATUS:     s_csr_add = MCSR_STATUS;
            CSR_MIE:         s_csr_add = MCSR_IE;
            CSR_MTVEC:       s_csr_add = MCSR_TVEC;
            CSR_MEPC:        s_csr_add = MCSR_EPC;
            CSR_MCAUSE:      s_csr_add = MCSR_CAUSE;
            CSR_MTVAL:       s_csr_add = MCSR_TVAL;
            CSR_MIP:         s_csr_add = MCSR_IP;
            CSR_MCYCLE:      s_csr_add = MCSR_CYCLE;
            CSR_MCYCLEH:     s_csr_add = MCSR_CYCLEH;
            CSR_MINSTRET:    s_csr_add = MCSR_INSTRET;
            CSR_MINSTRETH:   s_csr_add = MCSR_INSTRETH;
            CSR_MSCRATCH:    s_csr_add = MCSR_SCRATCH;
            CSR_MHARTID:     s_csr_add = MCSR_HARTID;
            CSR_MHRDCTRL0:   s_csr_add = MCSR_HRDCTRL0;
            CSR_MISA:        s_csr_add = MCSR_ISA;
`ifdef PROT_INTF
            CSR_MADDRERR:    s_csr_add = MCSR_ADDRERR;
`endif
            default:         s_csr_add = 5'b11111;
        endcase   
    end 

    //CSR auxiliary values
    assign s_csr_fun        = (s_mret) ? CSR_FUN_RET : (s_ecb & s_instr_i[20]) ? CSR_FUN_EBREAK : CSR_FUN_ECALL;
    assign s_csr_type       = s_instr_i[31:28];
    assign s_csr_need_rs1   = (~s_instr_i[14] & (s_instr_i[12] | s_instr_i[13]));

    //Instruction source specifier
    assign s_src_ctrl[SCTRL_RFRP1]  = (s_op | s_op_imm | s_branch | s_jalr | s_store | s_load | (s_csr & s_csr_need_rs1) | s_instr_ctrl[ICTRL_UNIT_BEU]);
    assign s_src_ctrl[SCTRL_RFRP2]  = (s_op | s_branch | s_store | s_b_shadd | s_b_clmul | s_b_minmax | s_b_rol | s_b_gates |
        (~s_b_op_imm & (s_b_bsetbext | s_b_binvbclr | s_b_ror | (s_b_misc & ~s_b_zexth))));
    assign s_src_ctrl[SCTRL_ZERO1]  = (s_rs1 == 5'b0) | s_lui;
    assign s_src_ctrl[SCTRL_ZERO2]  = s_rs2 == 5'b0;

    //Instruction control specifier
    assign s_instr_ctrl[ICTRL_UNIT_ALU] = ((s_op & ~s_m_op) | s_op_imm | s_auipc | s_lui | s_b_minmax);
    assign s_instr_ctrl[ICTRL_UNIT_BRU] = (s_branch | s_jal | s_jalr | s_fence);
    assign s_instr_ctrl[ICTRL_UNIT_LSU] = (s_store | s_load);
    assign s_instr_ctrl[ICTRL_UNIT_CSR] = (s_system);
    assign s_instr_ctrl[ICTRL_UNIT_MDU] = ((s_op & s_m_op) | s_b_clmul);
    assign s_instr_ctrl[ICTRL_UNIT_BEU] = (s_b_primary | s_b_secondary | s_b_tertiary);
    assign s_instr_ctrl[ICTRL_REG_DEST] = (|s_rd) & (s_lui | s_auipc | s_jal | s_jalr | s_op | s_op_imm | s_csr | s_load | s_instr_ctrl[ICTRL_UNIT_BEU]);
    assign s_instr_ctrl[ICTRL_RVC]      = 1'b0;
    //Prediction is not allowed from other instructions than branch/jump
    assign s_pred_not_allowed           = s_prediction_i & (~s_instr_ctrl[ICTRL_UNIT_BRU] | s_fence);
    assign s_instr_miscon               = s_illegal ? IMISCON_ILLE : s_pred_not_allowed ? IMISCON_DSCR : IMISCON_FREE;

endmodule
