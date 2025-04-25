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
    input logic s_compare_i,            // response from ALU
    input logic[31:0] s_op1_i,          // operand 1
    input logic[31:0] s_op2_i,          // operand 2
    output logic[31:0] s_result_o       // combinatorial result
);
    logic[5:0] s_cpop[32], s_ctz[32], s_clz[32];
    logic s_ctz_prev[32], s_clz_prev[32];
    logic[31:0] s_rev8, s_orcb;

    assign s_cpop[0] = {4'b0, s_op1_i[0]};
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

    genvar i;
    generate
        for(i = 1; i < 32; i++) begin: gen_bitcounting
            // calculate trailing zeros
            assign s_ctz_prev[i] = s_ctz_prev[i - 1] & ~s_op1_i[i];
            assign s_ctz[i]  = s_ctz[i - 1] + s_ctz_prev[i];

            // calculate leading zeros
            assign s_clz_prev[i] = s_clz_prev[i - 1] & ~s_op1_i[31 - i];
            assign s_clz[i]  = s_clz[i - 1] + s_clz_prev[i];

            // count set bits
            assign s_cpop[i] = s_cpop[i - 1] + s_op1_i[i];
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
            BEU_MINMAX:
                s_result_o = s_compare_i ? s_op2_i : s_op1_i;
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
                        s_result_o = {26'b0, s_cpop[31][5:0]};
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
    end

endmodule

