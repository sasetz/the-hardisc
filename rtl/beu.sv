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

import p_hardisc::*;

module beu (
    input f_part s_function_i,          // instruction function
    input logic s_compare_i,            // enable partial ALU operations
    input logic[31:0] s_op1_i,          // operand 1
    input logic[31:0] s_op2_i,          // operand 2
    output logic[31:0] s_result_o       // combinatorial result
);
    logic[5:0] s_ctz[32], s_clz[32], s_cpop;
    logic s_ctz_prev[32], s_clz_prev[32];
    logic[31:0] s_rev8, s_orcb;
    logic[3:0] s_byte_adder[4];

    ///////////////////////////////////////////////////////////////////////////
    assign s_ctz[0] = {4'b0, ~s_op1_i[0]};
    assign s_clz[0] = {4'b0, ~s_op1_i[31]};

    assign s_ctz_prev[0] = ~s_op1_i[0];
    assign s_clz_prev[0] = ~s_op1_i[31];

    // s_ctz_prev
    // it accumulates the data if we should continue to add zeros to the total
    // count or not. It needs to multiply its previous value with the current
    // bit in the op1. Then, this value is used to add up to the total count
    // of trailing/leading zeros
    //
    // 31  30  29  28  27  26  25  24  23  22  21  20  19  18  17  16  15 ...
    // [1] [1] [1] [0] [0] [0] [0] [0] [0] [0] [0] [0] [0] [0] [0] [0] [0]...
    //
    // ...if s_op1_i is the following
    //
    // 31  30  29  28  27  26  25  24  23  22  21  20  19  18  17  16  15 ...
    // [0] [0] [0] [1] [0] [1] [1] [0] [1] [0] [1] [0] [1] [1] [1] [1] [1]...
    //
    ///////////////////////////////////////////////////////////////////////////

    logic s_slt, s_sltu;
    assign s_slt = (s_op1_i[31] ^ s_op2_i[31]) ? s_op1_i[31] : s_sltu;
    assign s_sltu= s_op1_i < s_op2_i;

    // min, minu, max, maxu
    // there are no remaining bits left in the f_part for 4 new instructions,
    // so ALU cooperation was initially used here. Unfortunately it put too
    // much restrictions for synthesis, extending the critical path beyond the
    // desired limit
    //
    // here, the decoding is left intact, so the ALU function values are used.
    // This ALU replacement mode is activated in executor module through the
    // s_ictrl_i[ICTRL_UNIT_ALU]
    //
    ///////////////////////////////////////////////////////////////////////////

    assign s_byte_adder[0] = s_op1_i[0] + s_op1_i[1] + s_op1_i[2] + s_op1_i[3] +
                             s_op1_i[4] + s_op1_i[5] + s_op1_i[6] + s_op1_i[7];
    assign s_byte_adder[1] = s_op1_i[8] + s_op1_i[9] + s_op1_i[10] + s_op1_i[11] +
                             s_op1_i[12] + s_op1_i[13] + s_op1_i[14] + s_op1_i[15];
    assign s_byte_adder[2] = s_op1_i[16] + s_op1_i[17] + s_op1_i[18] + s_op1_i[19] +
                             s_op1_i[20] + s_op1_i[21] + s_op1_i[22] + s_op1_i[23];
    assign s_byte_adder[3] = s_op1_i[24] + s_op1_i[25] + s_op1_i[26] + s_op1_i[27] +
                             s_op1_i[28] + s_op1_i[29] + s_op1_i[30] + s_op1_i[31];

    assign s_cpop = s_byte_adder[0] + s_byte_adder[1] + s_byte_adder[2] + s_byte_adder[3];

    // parallel cpop
    // Here, to reduce the critical path, we split the addition into more
    // parts that are parallel to each other. Adding 8 bits is enough,
    // although a more elaborate design could probably decrease the critical
    // path even further
    //
    ///////////////////////////////////////////////////////////////////////////

    genvar i;
    generate
        for(i = 1; i < 32; i++) begin: gen_bitcounting
            // calculate trailing zeros
            assign s_ctz_prev[i] = s_ctz_prev[i - 1] & ~s_op1_i[i];
            assign s_ctz[i]  = s_ctz[i - 1] + s_ctz_prev[i];

            // calculate leading zeros
            assign s_clz_prev[i] = s_clz_prev[i - 1] & ~s_op1_i[31 - i];
            assign s_clz[i]  = s_clz[i - 1] + s_clz_prev[i];
        end
    endgenerate

    generate
        for (i = 0; i < 32; i += 8) begin: gen_rev8
            assign s_rev8[i +: 8] = s_op1_i[(31 - i) -: 8];
        end
    endgenerate

    generate
        for (i = 0; i < 32; i += 8) begin: gen_orcb
            assign s_orcb[i +: 8] = s_op1_i[i +: 8] == 8'b0 ? 8'b00000000 : 8'b11111111;
        end
    endgenerate

    always_comb begin : beu_comb
        if (~s_compare_i) begin
            case (s_function_i)
                BEU_SH1ADD:
                    s_result_o = s_op2_i + (s_op1_i << 1);
                BEU_SH2ADD:
                    s_result_o = s_op2_i + (s_op1_i << 2);
                BEU_SH3ADD:
                    s_result_o = s_op2_i + (s_op1_i << 3);
                BEU_BSET:
                    s_result_o = s_op1_i | (1 << s_op2_i[4:0]);
                BEU_BEXT:
                    s_result_o = {31'b0, s_op1_i[s_op2_i[4:0]]};
                BEU_BINV:
                    s_result_o = s_op1_i ^ (1 << s_op2_i[4:0]);
                BEU_BCLR:
                    s_result_o = s_op1_i & ~(1 << s_op2_i[4:0]);
                BEU_CLMUL: // FIXME: delete CLMUL or finish it
                    s_result_o = s_op1_i;
                BEU_MISC: begin
                    case (s_op2_i[11:0])
                        BEU_I_SEXTB:
                            s_result_o = {{24{s_op1_i[7]}}, s_op1_i[7:0]};
                        BEU_I_SEXTH:
                            s_result_o = {{16{s_op1_i[15]}}, s_op1_i[15:0]};
                        BEU_I_ZEXTH:
                            s_result_o = {16'b0, s_op1_i[15:0]};
                        BEU_I_REV8:
                            s_result_o = s_rev8;
                        BEU_I_ORCB:
                            s_result_o = s_orcb;
                        BEU_I_CLZ:
                            s_result_o = {26'b0, s_clz[31][5:0]};
                        BEU_I_CPOP:
                            s_result_o = {26'b0, s_cpop[5:0]};
                        BEU_I_CTZ:
                            s_result_o = {26'b0, s_ctz[31][5:0]};
                        default:
                            s_result_o = 32'd0;
                    endcase
                end
                BEU_ROR:
                    s_result_o =
                    (s_op1_i >> s_op2_i[4:0]) |
                    (s_op1_i << (32 - s_op2_i[4:0]));
                BEU_ROL:
                    s_result_o =
                    (s_op1_i << s_op2_i[4:0]) |
                    (s_op1_i >> (32 - s_op2_i[4:0]));
                BEU_XNOR:
                    s_result_o = ~(s_op1_i ^ s_op2_i);
                BEU_ANDN:
                    s_result_o = s_op1_i & ~(s_op2_i);
                BEU_ORN:
                    s_result_o = s_op1_i | ~(s_op2_i);
                default:
                    s_result_o = 32'd0;
            endcase
        end else begin // enable BEU to execute some of the ALU functions
            case (s_function_i)
                ALU_SLT:
                    s_result_o = ~s_slt ? s_op1_i : s_op2_i;
                ALU_SLTU:
                    s_result_o = ~s_sltu ? s_op1_i : s_op2_i;
                ALU_GE:
                    s_result_o = s_slt ? s_op1_i : s_op2_i;
                ALU_GEU:
                    s_result_o = s_sltu ? s_op1_i : s_op2_i;
                default:
                    s_result_o = 32'd0;
            endcase
        end
    end

endmodule

