
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

// carry-less multiplication module
module carmul (
    input  logic       s_clk_i,        // clock
    input  logic       s_resetn_i,     // active‐low reset
    input  f_part      s_function_i,   // instruction function
    input  logic[31:0] s_op1_i,        // operand 1
    input  logic[31:0] s_op2_i,        // operand 2

    input  logic       s_stall_i,      // stall (preserve state)
    input  logic       s_flush_i,      // flush pipeline
    input  logic       s_compute_i,    // start CLMUL
    output logic       s_finished_o,   // computation finished
    output logic[31:0] s_result_o      // combinatorial result
);
    logic[62:0] s_wproduct[1], s_rproduct[1]; // partial and final product
    logic[5:0]  s_wcounter[1], s_rcounter[1]; // cycle counter
    logic[62:0] s_woperand[1], s_roperand[1]; // operand that shifts left
    logic[31:0] s_wconsume[1], s_rconsume[1]; // operand shift register
    logic s_started, s_finished,      // helper signals
        s_direct_result;

    // partial and final product
    seu_ff_we  #(.LABEL("BE_RPROD"), .W(63), .N(1))
    m_seu_rproduct(
        .s_c_i({s_clk_i}),
        .s_we_i({s_compute_i}),
        .s_d_i(s_wproduct),
        .s_q_o(s_rproduct)
    );

    // reset to all-ones
    seu_ff_rst #(.LABEL("BE_RCNTR"), .W(6), .N(1))
    m_seu_rcounter(
        .s_c_i({s_clk_i}),
        .s_r_i({s_resetn_i}),
        .s_d_i(s_wcounter),
        .s_q_o(s_rcounter)
    );

    // store the operand across cycles
    seu_ff_we  #(.LABEL("BE_ROPER"), .W(63), .N(1))
    m_seu_roperand(
        .s_c_i({s_clk_i}),
        .s_we_i({s_compute_i}),
        .s_d_i(s_woperand),
        .s_q_o(s_roperand)
    );

    // shift the other operand across cycles
    seu_ff_we  #(.LABEL("BE_RCONS"), .W(32), .N(1))
    m_seu_rconsume(
        .s_c_i({s_clk_i}),
        .s_we_i({s_compute_i}),
        .s_d_i(s_wconsume),
        .s_q_o(s_rconsume)
    );

    ///////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////

    // implementation
    assign s_started    = s_rcounter[0] != 6'b000000;
    assign s_finished   = s_rcounter[0] == 6'b111111;
    assign s_finished_o = s_finished;
    assign s_direct_result  = ~(|s_op1_i) | ~(|s_op2_i);
    assign s_zero           = ~(|s_rconsume[0]);

    // product calculation
    always_comb begin : cmu_product
        if (s_compute_i & ~s_started) begin
            // Start of computation
            if (s_direct_result) begin
                // If either operand is zero, the product is zero
                s_wproduct[0] = 63'b0;
            end else begin
                // Start of multiplication
                s_wproduct[0] = {32{s_op1_i[0]}} & s_op2_i;
            end
            s_woperand[0]   = s_op2_i << 1;
            s_wconsume[0]   = s_op1_i >> 1;
        end else if (s_started & ~s_finished) begin // main calculation
            s_wproduct[0] = s_rproduct[0] ^ ({63{s_rconsume[0][0]}} & s_roperand[0]);
            s_woperand[0] = s_roperand[0] << 1;
            s_wconsume[0] = s_rconsume[0] >> 1;
        end else if (s_stall_i) begin
            // Preserve the result, if the computation has finished and the MA stage is not ready
            s_woperand[0]   = s_roperand[0];
            s_wproduct[0]   = s_rproduct[0];
            s_wconsume[0]   = s_rconsume[0];
        end else begin
            s_woperand[0]   = 32'b0;
            s_wproduct[0]   = 63'b0;
            s_wconsume[0]   = 32'b0;
        end
    end

    // control logic
    always_comb begin : cmu_control
        if (s_flush_i) begin
            s_wcounter[0]   = 6'd0;
        end else if (s_compute_i & ~s_started) begin // start
            if (s_direct_result) begin
                s_wcounter[0]   = 6'b111111; // results are ready
            end else begin
                s_wcounter[0]   = 6'b000001; // counter goes up
            end
        end else if (s_started & ~s_finished) begin // main computation
            // Optimization: is the remaining multiplier zero? finish the computation
            s_wcounter[0] = s_zero ? 6'b111111 : s_rcounter[0] + 6'd1;
            if (s_rcounter[0] == 6'd32) begin
                s_wcounter[0] = 6'b111111; // we don't need to count anymore
            end
        end else if (s_stall_i) begin
            s_wcounter[0]   = s_rcounter[0];
        end else begin
            s_wcounter[0]   = 6'd0;
        end
    end

    always_comb begin : cmu_select
        case (s_function_i)
            CMU_CLMUL:
                s_result_o = s_rproduct[0][31:0];
            CMU_CLMULH:
                s_result_o = {1'b0, s_rproduct[0][62:32]}; // msb is always 0
            CMU_CLMULR:
                s_result_o = {s_rproduct[0][62:31]};
            default:
                s_result_o = 32'd1337;
        endcase
    end
endmodule
