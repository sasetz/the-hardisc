//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 07/31/2022 07:20:56 AM
// Design Name: 
// Module Name: ahb_to_uart_controller
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////


module ahb_to_uart_controller#(
    parameter PERIOD = 10,
    parameter SIMULATION = 0
)
(
    input s_clk_i,
    input s_resetn_i,
    
    //AHB3-Lite
    input [31:0] s_haddr_i,
    input [31:0] s_hwdata_i,
    input s_hready_i,
    input [2:0]s_hburst_i,
    input s_hmastlock_i,
    input [3:0]s_hprot_i,
    input [2:0]s_hsize_i,
    input [1:0]s_htrans_i,
    input s_hwrite_i,
    input s_hsel_i,
    
    output [31:0] s_hrdata_o,
    output s_hready_o,
    output s_hresp_o,

    output s_data_ready_o,

    //UART
    input s_rxd_i,
    output s_txd_o
);
    //Control
    logic r_write, r_uart_active, r_hresp, r_trans, r_add;
    logic r_uart_state, r_uart_accepted;

    //UART
    logic s_uart_start, s_uart_busy, s_error, s_uart_data_rdy;
    logic[7:0] s_data, s_rec_data, r_uart_data;

    assign s_error  = 1'b0;

    assign s_hrdata_o = {24'b0, r_add ? {7'b0,r_uart_state} : r_uart_data};
    assign s_hready_o = ~(r_write & ~r_add);
    assign s_hresp_o  = r_hresp;

    assign s_data_ready_o   = r_uart_state;

    assign s_uart_start  = r_write & ~r_hresp & r_trans & ~r_add;
    assign s_data        = s_hwdata_i[7:0];

    always @ (posedge s_clk_i or negedge s_resetn_i) begin
        if(~s_resetn_i)begin
            r_write         <= 1'd0;
            r_hresp         <= 1'd0;
            r_trans         <= 1'd0;
            r_add           <= 1'd0;
        end else if(r_write & ~r_add) begin
            r_hresp         <= r_hresp;
            r_write         <= (s_uart_busy | r_trans) ? r_write : 1'd0;
            r_trans         <= 1'd0;
            r_add           <= r_add;
        end else if((s_htrans_i == 2'd2) & s_hsel_i)begin
            r_write         <= s_hwrite_i; 
            r_hresp         <= s_error;
            r_trans         <= 1'd1;
            r_add           <= s_haddr_i[2];
        end else begin
            r_hresp         <= 1'd0;
            r_write         <= 1'd0;
            r_trans         <= 1'd0;
            r_add           <= 1'd0;
        end
    end

    always_ff @(posedge s_clk_i or negedge s_resetn_i) begin
        if(~s_resetn_i)begin
            r_uart_data     <= 8'd65;
            r_uart_accepted <= 1'b0;
        end else if(s_uart_data_rdy & ~r_uart_accepted)begin
            r_uart_data     <= s_rec_data;
            r_uart_accepted <= 1'd1;
        end else if(s_uart_data_rdy & r_uart_accepted)begin
            r_uart_data     <= r_uart_data;
            r_uart_accepted <= 1'b1;
        end else begin
            r_uart_data     <= r_uart_data;
            r_uart_accepted <= 1'b0;
        end
        if(~s_resetn_i)begin
            r_uart_state    <= 1'd0;
        end else if(r_write & ~r_hresp & r_trans & r_add) begin
            r_uart_state    <= s_hwdata_i[0];
        end else begin
            r_uart_state    <= r_uart_accepted ? r_uart_state : s_uart_data_rdy;
        end

    end


    uart_controller#(.PERIOD(PERIOD)) uart
    (
        .s_clk_i(s_clk_i),
        .s_resetn_i(s_resetn_i),
        .s_rxd_i(s_rxd_i),
        .s_request_i(s_uart_start),
        .s_txd_o(s_txd_o),
        .s_data_i(s_data),
        .s_data_o(s_rec_data),
        .s_data_ready_o(s_uart_data_rdy),
        .s_busy_o(s_uart_busy)
    );
endmodule
