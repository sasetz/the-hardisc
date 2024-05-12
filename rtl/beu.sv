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
    input f_part s_function_i,          //instruction function
    input logic s_compare_i,            // response from ALU
    input logic[31:0] s_op1_i,          //operand 1
    input logic[31:0] s_op2_i,          //operand 2
    output logic[31:0] s_result_o       //combinatorial result
);
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
                    BEU_I_REV8: begin : rev8_logic
                        for (integer i = 0; i < 32; i += 8) begin
                            s_result_o[i +: 8] =
                                s_op1_i[(31 - i) -: 8];
                        end
                    end
                    BEU_I_ORCB: begin : orcb_logic
                        for (integer i = 0; i < 32; i += 8) begin
                            s_result_o[i +: 8] = s_op1_i[i +: 8] == 8'b0 ?
                                8'b00000000 : 8'b11111111;
                        end
                    end
                    BEU_I_CLZ: begin : clz_logic
                        logic[31:0] s_clear_count;
                        logic[31:0] s_previous_result;
                        s_previous_result[0] = s_op1_i[31] == 1'b0 ? 1'b1 : 1'b0;
                        s_clear_count = {31'b0, s_previous_result[0]};
                        for (integer i = 1; i < 32; i++) begin
                            s_previous_result[i] = s_previous_result[i - 1] &
                                (s_op1_i[31 - i] == 1'b0 ? 1'b1 : 1'b0);
                            s_clear_count += s_previous_result[i - 1] &
                                (s_op1_i[31 - i] == 1'b0 ? 1'b1 : 1'b0);
                        end
                        s_result_o = s_clear_count;
                    end
                    BEU_I_CPOP: begin : cpop_logic
                        logic[31:0] s_pop_count;
                        s_pop_count = 32'd0;
                        for (integer i = 0; i < 32; i++) begin
                            s_pop_count += s_op1_i[i];
                        end
                        s_result_o = s_pop_count;
                    end
                    BEU_I_CTZ: begin : ctz_logic
                        logic[31:0] s_clear_count;
                        logic[31:0] s_previous_result;
                        s_previous_result[0] = s_op1_i[0] == 1'b0 ? 1'b1 : 1'b0;
                        s_clear_count = {31'b0, s_previous_result[0]};
                        for (integer i = 1; i < 32; i++) begin
                            s_previous_result[i] = s_previous_result[i - 1] &
                                (s_op1_i[i] == 1'b0 ? 1'b1 : 1'b0);
                            s_clear_count += s_previous_result[i - 1] &
                                (s_op1_i[i] == 1'b0 ? 1'b1 : 1'b0);
                        end
                        s_result_o = s_clear_count;
                    end
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

