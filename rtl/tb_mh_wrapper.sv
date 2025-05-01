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
import edac::*;

//`timescale 1ps/1ps

`ifdef PROT_INTF
    `define MEMORY_IFP 1
    `define INTF_REPS  3 
    `define SYSTEM system_hardisc //available systems: system_hardisc, system_dcls
`else
    `define MEMORY_IFP 0
    `define INTF_REPS  1
    `define SYSTEM system_core 
`endif

module tb_mh_wrapper(
    input s_clk_i,
    input s_resetn_i,

    //input qspi_miso,
    //output qspi_cs,
    //output qspi_mosi,

    //input btnc,
    //input btnd,
    //input btnl,
    //input btnr,
    //input btnu,
    //input ps2_clk,
    //input ps2_data,
    
    //output ja[3],
    output led[4],

    input uart_txd_in,
    output uart_rxd_out
);

localparam SUBORDINATES = 4;
localparam MEM_SIZE = 32'h20000;
localparam MEM_MSB  = $clog2(MEM_SIZE) - 32'h1;
localparam BOOTADD  = 32'h00000000;
localparam pma_cfg_t PMA_CONFIG[SUBORDINATES] = '{
    '{base  : 32'h00000000, mask  : 32'hFFFFFF00, read_only  : 1'b1, executable: 1'b1, idempotent : 1'b1},
    '{base  : 32'h10000000, mask  : 32'hFFFE0000, read_only  : 1'b0, executable: 1'b1, idempotent : 1'b1},
    '{base  : 32'h80000000, mask  : 32'hFFFFF400, read_only  : 1'b0, executable: 1'b1, idempotent : 1'b1},
    '{base  : 32'h80001000, mask  : 32'hFFFFF400, read_only  : 1'b0, executable: 1'b1, idempotent : 1'b1}
};

logic[5:0] s_i_hparity[1];
logic[6:0] s_i_hrchecksum[1], s_i_hwchecksum[1];
logic[31:0] s_i_hrdata[1], s_i_haddr[1], s_i_hwdata[1];
logic s_i_hwrite[1], s_i_hmastlock[1],s_i_hready[`INTF_REPS],s_i_hresp[`INTF_REPS];
logic[1:0] s_i_htrans[1];
logic[2:0] s_i_hsize[1],s_i_hburst[1];
logic[3:0] s_i_hprot[1];

logic[5:0] s_d_hparity[1];
logic[6:0] s_d_hrchecksum[1], s_d_hwchecksum[1];
logic[31:0] s_d_hrdata[1], s_d_haddr[1], s_d_hwdata[1];
logic s_d_hwrite[1], s_d_hmastlock[1],s_d_hready[`INTF_REPS],s_d_hresp[`INTF_REPS];
logic[1:0] s_d_htrans[1];
logic[2:0] s_d_hsize[1],s_d_hburst[1];
logic[3:0] s_d_hprot[1];

logic[6:0] s_shrchecksum[3];
logic[31:0] s_shrdata[3];
logic s_shready[3], s_shresp[3], s_shsel[3];
logic[31:0] s_ahb_sbase[3], s_ahb_smask[3];

logic[6:0] s_chrchecksum[2];
logic[31:0] s_chrdata[2];
logic s_chready[2], s_chresp[2], s_chsel[2];
logic[31:0] s_ahb_cbase[2], s_ahb_cmask[2];

logic s_sys_clk, s_sys_rstn, s_int_meip, s_int_mtip, s_unrec_err[2], s_locked;
logic s_dut_clk[3], s_dut_rstn[3];
/*
logic r_ver_clk, r_ver_rstn, r_test;

initial begin
    r_ver_clk   = 1'b1;
    r_ver_rstn  = 1'b0;
    r_test = 1'b0;
    #101;
    r_ver_rstn  = 1'b1; 
    #10000;
    r_test = 1'b1;
    #100;
    r_test = 1'b0;
end

always #5 r_ver_clk = ~r_ver_clk;

assign s_sys_clk    = r_ver_clk;
assign s_sys_rstn   = r_ver_rstn;
*/

//assign s_sys_clk    = s_clk_i;
clk_wiz_0 
 (
  .clk_out1(s_sys_clk),
  .resetn(s_resetn_i),
  .locked(s_locked),
  .clk_in1(s_clk_i)
 );

//synchronization of reset de-assertion
xpm_cdc_async_rst #(
   .DEST_SYNC_FF(4),    // DECIMAL; range: 2-10
   .INIT_SYNC_FF(0),    // DECIMAL; 0=disable simulation init values, 1=enable simulation init values
   .RST_ACTIVE_HIGH(0)  // DECIMAL; 0=active low reset, 1=active high reset
) xpm_cdc_async_rst_inst (
   .dest_clk(s_sys_clk),  // 1-bit input: Destination clock.
   .src_arst(s_resetn_i & s_locked), // 1-bit input: Source asynchronous reset signal.
   .dest_arst(s_sys_rstn) // 1-bit output: src_arst asynchronous reset signal synchronized to destination
                          // clock domain. This output is registered. NOTE: Signal asserts asynchronously
                          // but deasserts synchronously to dest_clk. Width of the reset signal is at least
                          // (DEST_SYNC_FF*dest_clk) period.
);
// End of xpm_cdc_async_rst_inst instantiation

assign led[0]   = s_chsel[0]; //rom
assign led[1]   = s_chsel[1]; //ram

assign s_int_meip   = s_uart_interrupt;

/*ila_0 ila_0_test (
    .clk(s_sys_clk),
    .probe0(dut.s_rst_point[0]),
    .probe1(dut.m_pipe_5_ma.m_csru.s_mcycle[0]),
    .probe2(ahb_uart.r_uart_data),
    .probe3(s_uart_interrupt),
    .probe4(uart_txd_in)
);*/

assign s_dut_clk[0] = s_sys_clk;
assign s_dut_clk[1] = s_sys_clk;
assign s_dut_clk[2] = s_sys_clk;

assign s_dut_rstn[0] = s_sys_rstn;
assign s_dut_rstn[1] = s_sys_rstn;
assign s_dut_rstn[2] = s_sys_rstn;

(* dont_touch = "yes" *) `SYSTEM #(.PMA_REGIONS(SUBORDINATES),.PMA_CFG(PMA_CONFIG)) dut
(
    .s_clk_i(s_dut_clk),
    .s_resetn_i(s_dut_rstn),
    .s_int_meip_i(s_int_meip),
    .s_int_mtip_i(s_int_mtip),
    .s_boot_add_i(BOOTADD),
    
    .s_i_hrdata_i(s_i_hrdata[0]),
    .s_i_hready_i(s_i_hready),
    .s_i_hresp_i(s_i_hresp),
    .s_i_haddr_o(s_i_haddr[0]),
    .s_i_hwdata_o(s_i_hwdata[0]),
    .s_i_hburst_o(s_i_hburst[0]),
    .s_i_hmastlock_o(s_i_hmastlock[0]),
    .s_i_hprot_o(s_i_hprot[0]),
    .s_i_hsize_o(s_i_hsize[0]),
    .s_i_htrans_o(s_i_htrans[0]),
    .s_i_hwrite_o(s_i_hwrite[0]),

    .s_i_hrchecksum_i(s_i_hrchecksum[0]),
    .s_i_hwchecksum_o(s_i_hwchecksum[0]),
    .s_i_hparity_o(s_i_hparity[0]),

    .s_d_hrdata_i(s_d_hrdata[0]),
    .s_d_hready_i(s_d_hready),
    .s_d_hresp_i(s_d_hresp),
    .s_d_haddr_o(s_d_haddr[0]),
    .s_d_hwdata_o(s_d_hwdata[0]),
    .s_d_hburst_o(s_d_hburst[0]),
    .s_d_hmastlock_o(s_d_hmastlock[0]),
    .s_d_hprot_o(s_d_hprot[0]),
    .s_d_hsize_o(s_d_hsize[0]),
    .s_d_htrans_o(s_d_htrans[0]),
    .s_d_hwrite_o(s_d_hwrite[0]),

    .s_d_hrchecksum_i(s_d_hrchecksum[0]),
    .s_d_hwchecksum_o(s_d_hwchecksum[0]),
    .s_d_hparity_o(s_d_hparity[0]),

    .s_unrec_err_o(s_unrec_err)
);

`ifdef PROT_INTF
//replication is at the ouput of the interconnects
assign s_d_hready[1]    = s_d_hready[0];
assign s_d_hready[2]    = s_d_hready[0];
assign s_d_hresp[1]     = s_d_hresp[0];
assign s_d_hresp[2]     = s_d_hresp[0];
assign s_i_hready[1]    = s_i_hready[0];
assign s_i_hready[2]    = s_i_hready[0];
assign s_i_hresp[1]     = s_i_hresp[0];
assign s_i_hresp[2]     = s_i_hresp[0];
`endif

ahb_interconnect #(.SLAVES(2)) instr_interconnect
(
    .s_clk_i(s_sys_clk),
    .s_resetn_i(s_sys_rstn),

    .s_mhaddr_i(s_i_haddr[0]),
    .s_mhtrans_i(s_i_htrans[0]),

    .s_sbase_i(s_ahb_cbase),
    .s_smask_i(s_ahb_cmask),

    .s_shrdata_i(s_chrdata),
    .s_shready_i(s_chready),
    .s_shresp_i(s_chresp),
    .s_hsel_o(s_chsel),

    .s_shrchecksum_i(s_chrchecksum),
    .s_shrchecksum_o(s_i_hrchecksum[0]),
    
    .s_shrdata_o(s_i_hrdata[0]),
    .s_shready_o(s_i_hready[0]),
    .s_shresp_o(s_i_hresp[0])
);

ahb_interconnect #(.SLAVES(3)) data_interconnect
(
    .s_clk_i(s_sys_clk),
    .s_resetn_i(s_sys_rstn),

    .s_mhaddr_i(s_d_haddr[0]),
    .s_mhtrans_i(s_d_htrans[0]),

    .s_sbase_i(s_ahb_sbase),
    .s_smask_i(s_ahb_smask),

    .s_shrdata_i(s_shrdata),
    .s_shready_i(s_shready),
    .s_shresp_i(s_shresp),
    .s_hsel_o(s_shsel),

    .s_shrchecksum_i(s_shrchecksum),
    .s_shrchecksum_o(s_d_hrchecksum[0]),
    
    .s_shrdata_o(s_d_hrdata[0]),
    .s_shready_o(s_d_hready[0]),
    .s_shresp_o(s_d_hresp[0])
);

ahb_to_uart_controller #(.PERIOD(32'd160),.SIMULATION(0)) ahb_uart
(
    .s_clk_i(s_sys_clk),
    .s_resetn_i(s_sys_rstn),
    
    //AHB3-Lite
    .s_haddr_i(s_d_haddr[0]),
    .s_hwdata_i(s_d_hwdata[0]),
    .s_hready_i(s_d_hready[0]),
    .s_hburst_i(s_d_hburst[0]),
    .s_hmastlock_i(s_d_hmastlock[0]),
    .s_hprot_i(s_d_hprot[0]),
    .s_hsize_i(s_d_hsize[0]),
    .s_htrans_i(s_d_htrans[0]),
    .s_hwrite_i(s_d_hwrite[0]),
    .s_hsel_i(s_shsel[1]),
    
    .s_hrdata_o(s_shrdata[1]),
    .s_hready_o(s_shready[1]),
    .s_hresp_o(s_shresp[1]),
    
    .s_data_ready_o(s_uart_interrupt),

    .s_rxd_i(uart_txd_in),
    .s_txd_o(uart_rxd_out)
);

ahb_timer #(.IFP(`MEMORY_IFP)) m_mtimer
(
    .s_clk_i(s_sys_clk),
    .s_resetn_i(s_sys_rstn),
    
    //AHB3-Lite
    .s_haddr_i(s_d_haddr[0]),
    .s_hwdata_i(s_d_hwdata[0]),
    .s_hburst_i(s_d_hburst[0]),
    .s_hmastlock_i(s_d_hmastlock[0]),
    .s_hprot_i(s_d_hprot[0]),
    .s_hsize_i(s_d_hsize[0]),
    .s_htrans_i(s_d_htrans[0]),
    .s_hwrite_i(s_d_hwrite[0]),
    .s_hsel_i(s_shsel[2]),

    .s_hparity_i(s_d_hparity[0]),
    .s_hwchecksum_i(s_d_hwchecksum[0]),
    .s_hrchecksum_o(s_shrchecksum[2]),
    
    .s_hrdata_o(s_shrdata[2]),
    .s_hready_o(s_shready[2]),
    .s_hresp_o(s_shresp[2]),

    .s_timeout_o(s_int_mtip)
);

//ahb_ram #(.MEM_SIZE(32'h100),.MEM_INIT(1),.MEM_FILE("bootloader.mem"),.SIMULATION(0),.LABEL("BOOT"),.IFP(`MEMORY_IFP),.GROUP(SEEGR_MEMORY),.MPROB(0)) m_boot
ahb_ram #(.MEM_SIZE(32'h100),.SIMULATION(0),.LABEL("BOOT"),.IFP(`MEMORY_IFP),.GROUP(SEEGR_MEMORY),.MPROB(0)) m_boot
(
    .s_clk_i(s_sys_clk),
    .s_resetn_i(s_sys_rstn),
    
    //AHB3-Lite
    .s_haddr_i(s_i_haddr[0]),
    .s_hwdata_i(s_i_hwdata[0]),
    .s_hburst_i(s_i_hburst[0]),
    .s_hmastlock_i(s_i_hmastlock[0]),
    .s_hprot_i(s_i_hprot[0]),
    .s_hsize_i(s_i_hsize[0]),
    .s_htrans_i(s_i_htrans[0]),
    .s_hwrite_i(s_i_hwrite[0]),
    .s_hsel_i(s_chsel[0]),

    .s_hparity_i(s_i_hparity[0]),
    .s_hwchecksum_i(s_i_hwchecksum[0]),
    .s_hrchecksum_o(s_chrchecksum[0]),
    
    .s_hrdata_o(s_chrdata[0]),
    .s_hready_o(s_chready[0]),
    .s_hresp_o(s_chresp[0])
);

logic s_m_hmastlock[2], s_m_hwrite[2], s_m_hsel[2], s_m_hready[2], s_m_hresp[2];
logic[1:0] s_m_htrans[2];
logic[2:0] s_m_hburst[2],s_m_hsize[2];
logic[3:0] s_m_hprot[2];
logic[31:0] s_m_haddr[2];
logic[31:0] s_m_hwdata[2], s_m_hrdata[2];
logic[6:0] s_m_hwchecksum[2], s_m_hrchecksum[2];
logic[5:0] s_m_hparity[2];

assign s_m_hmastlock   = {s_d_hmastlock[0], s_i_hmastlock[0]};
assign s_m_hwrite      = {s_d_hwrite[0], s_i_hwrite[0]};
assign s_m_hsel        = {s_shsel[0], s_chsel[1]};
assign s_m_htrans      = {s_d_htrans[0], s_i_htrans[0]};
assign s_m_hburst      = {s_d_hburst[0], s_i_hburst[0]};
assign s_m_hsize       = {s_d_hsize[0], s_i_hsize[0]};
assign s_m_hprot       = {s_d_hprot[0], s_i_hprot[0]};
assign s_m_haddr       = {s_d_haddr[0], s_i_haddr[0]};
assign s_m_hwdata      = {s_d_hwdata[0], s_i_hwdata[0]};
assign s_m_hwchecksum  = {s_d_hwchecksum[0], s_i_hwchecksum[0]};
assign s_m_hparity     = {s_d_hparity[0], s_i_hparity[0]};

assign s_chready[1]     = s_m_hready[1];
assign s_chresp[1]      = s_m_hresp[1];
assign s_chrdata[1]     = s_m_hrdata[1];
assign s_chrchecksum[1] = s_m_hrchecksum[1];

assign s_shready[0]     = s_m_hready[0];
assign s_shresp[0]      = s_m_hresp[0];
assign s_shrdata[0]     = s_m_hrdata[0];
assign s_shrchecksum[0] = s_m_hrchecksum[0];

//dahb_ram #(.MEM_SIZE(MEM_SIZE),.SIMULATION(0),.ENABLE_LOG(0),.MEM_INIT(1),.MEM_FILE("test.mem"),.LABEL("MEMORY"),.IFP(`MEMORY_IFP),.GROUP(SEEGR_MEMORY)) m_memory
dahb_ram #(.MEM_SIZE(MEM_SIZE),.SIMULATION(0),.ENABLE_LOG(0),.LABEL("MEMORY"),.IFP(`MEMORY_IFP),.GROUP(SEEGR_MEMORY)) m_memory
(
    .s_clk_i(s_sys_clk),
    .s_resetn_i(s_sys_rstn),
    
    //AHB3-Lite
    .s_haddr_i(s_m_haddr),
    .s_hwdata_i(s_m_hwdata),
    .s_hburst_i(s_m_hburst),
    .s_hmastlock_i(s_m_hmastlock),
    .s_hprot_i(s_m_hprot),
    .s_hsize_i(s_m_hsize),
    .s_htrans_i(s_m_htrans),
    .s_hwrite_i(s_m_hwrite),
    .s_hsel_i(s_m_hsel),

    .s_hparity_i(s_m_hparity),
    .s_hwchecksum_i(s_m_hwchecksum),
    .s_hrchecksum_o(s_m_hrchecksum),
    
    .s_hrdata_o(s_m_hrdata),
    .s_hready_o(s_m_hready),
    .s_hresp_o(s_m_hresp)
);

genvar s;
generate
    for(s=1;s<SUBORDINATES;s++)begin
        assign s_ahb_sbase[s-1]   = PMA_CONFIG[s].base;
        assign s_ahb_smask[s-1]   = PMA_CONFIG[s].mask;
    end
    for(s=0;s<2;s++)begin
        assign s_ahb_cbase[s]   = PMA_CONFIG[s].base;
        assign s_ahb_cmask[s]   = PMA_CONFIG[s].mask;
    end
endgenerate
endmodule
