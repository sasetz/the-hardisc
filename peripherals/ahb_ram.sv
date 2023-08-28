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

import seed_instance::*;

module ahb_ram#(
    parameter MEM_SIZE = 32'h00001000,
    parameter SIMULATION = 0,
    parameter ENABLE_LOG = 1,
    parameter LABEL = "MEMORY"
)
(
    input s_clk_i,
    input s_resetn_i,
    
    //AHB3-Lite
    input [$clog2(MEM_SIZE)-1:0] s_haddr_i,
    input [31:0] s_hwdata_i,
    input [2:0]s_hburst_i,
    input s_hmastlock_i,
    input [3:0]s_hprot_i,
    input [2:0]s_hsize_i,
    input [1:0]s_htrans_i,
    input s_hwrite_i,
    input s_hsel_i,
    
    output [31:0] s_hrdata_o,
    output s_hready_o,
    output s_hresp_o
);
    localparam MSB = $clog2(MEM_SIZE) - 32'h1;

    logic[31:0] s_read_data, s_write_data;
    logic[MSB:0] r_address, r_paddress, s_ra;
    logic[1:0] r_size;
    logic r_write, r_trans;
    logic[31:0] r_memory[MEM_SIZE[31:2]] = '{default:0};
    logic[31:0] r_data, r_wtor_data;
    logic s_wea[4];
    logic s_we, r_wtor, s_cclock;

generate
    logic[1:0] r_delay;

    if(SIMULATION == 1)begin
        int logging;
        logic latency, l_clock;
        logic[31:0] seed, randomval;

        initial begin
            latency = 0;
            logging = 0;
            seed_instance::srandom($sformatf("%m"));
            if($value$plusargs ("LOGGING=%d", logging));
            if($value$plusargs ("LAT=%d", latency));
            seed = $urandom;
            if(latency != 0)
                $write("MEMORY LATENCY SEED: %d\n",seed);
        end

        if(ENABLE_LOG == 1)begin
            always_ff @( posedge s_clk_i ) begin : trace
                if(s_we)begin
                    if(logging == 0)begin
                        $write("%c",s_write_data);
                    end else if(logging > 1)begin
                        $write("Storing of %x to %s[%x]\n",s_write_data,LABEL,r_address);
                    end
                end
            end
        end

        always_ff @(posedge s_clk_i) begin : delay_control
            if(~s_resetn_i | ~latency)begin
                r_delay   <= 2'b0;
                randomval <= 32'b0; 
            end else if(r_delay != 2'b0)begin
                r_delay   <= r_delay - 2'b1;
                randomval <= randomval;
            end else if(s_hsel_i & (s_htrans_i == 2'd2))begin
                r_delay   <= randomval[1:0];
                randomval <= $urandom(seed+randomval);
            end else begin
                r_delay   <= 2'b0;
                randomval <= randomval;
            end
        end
        always_latch begin : clockgating
            if(~s_clk_i)
                l_clock <= (r_delay == 2'b00);
        end
        assign s_cclock = s_clk_i & l_clock;
        assign s_we     = r_write & (r_delay == 2'b00);
        assign s_ra     = (r_delay == 2'b00) ? s_haddr_i : r_address;
    end else begin
        assign s_cclock = s_clk_i;
        assign s_we     = r_write;
        assign s_ra     = s_haddr_i;
        assign r_delay  = 2'b0;
    end
endgenerate

    assign s_read_data = (r_wtor & (r_address[MSB:2] == r_paddress[MSB:2])) ? r_wtor_data : r_data;
    assign s_hrdata_o = s_read_data;
    assign s_hready_o = r_delay == 2'b00;
    assign s_hresp_o = 1'b0;

    assign s_wea[0] = s_we & (r_address[1:0] == 2'd0);
    assign s_wea[1] = s_we & (((r_address[1:0] == 2'd0) & (r_size != 2'd0)) || (r_address[1:0] == 2'd1));
    assign s_wea[2] = s_we & (((r_address[1:0] == 2'd0) & (r_size == 2'd2)) || (r_address[1:0] == 2'd2));
    assign s_wea[3] = s_we & (((r_address[1:0] == 2'd0) & (r_size == 2'd2)) || ((r_address[1:0] == 2'd2) & (r_size == 2'd1)) || (r_address[1:0] == 2'd3));
    assign s_write_data[7:0]    = s_wea[0] ? s_hwdata_i[7:0] : s_read_data[7:0];
    assign s_write_data[15:8]   = s_wea[1] ? s_hwdata_i[15:8] : s_read_data[15:8];
    assign s_write_data[23:16]  = s_wea[2] ? s_hwdata_i[23:16] : s_read_data[23:16];
    assign s_write_data[31:24]  = s_wea[3] ? s_hwdata_i[31:24] : s_read_data[31:24];

    generate
    genvar i;
        for (i = 0; i < 4; i = i+1) begin: byte_write
            always @(posedge s_clk_i)
                if (s_wea[i])
                    r_memory[r_address[MSB:2]][(i+1)*8-1:i*8] <= s_hwdata_i[(i+1)*8-1:i*8];
        end
    endgenerate

    always_ff @(posedge s_clk_i) begin : memory_read
        r_data <= r_memory[s_ra[MSB:2]];
    end

    always_ff @(posedge s_cclock) begin : memory_control
        if(~s_resetn_i)begin
            r_trans <= 1'd0;
            r_write <= 1'd0;
            r_address <= {1'b0,{MSB{1'b0}}};
            r_paddress <= {1'b0,{MSB{1'b0}}};
            r_wtor_data <= 32'b0;
            r_size <= 2'd0;
            r_wtor <= 1'b0;
        end else if(s_hsel_i & (s_htrans_i == 2'd2))begin
            r_trans <= 1'd1;
            r_write <= s_hwrite_i;
            r_address <= s_haddr_i;
            r_paddress <= r_address;
            r_wtor_data <= s_write_data;
            r_size <= s_hsize_i[1:0];
            r_wtor <= s_we;
        end else begin
            r_trans <= 1'd0;
            r_write <= 1'd0;
            r_address <= r_address;
            r_paddress <= r_address;
            r_wtor_data <= r_wtor_data;
            r_size <= 2'd0;
            r_wtor <= 1'b0;
        end
    end

endmodule