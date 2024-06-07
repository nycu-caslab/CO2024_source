`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 02/08/2024 02:59:36 PM
// Design Name: 
// Module Name: cpu_top
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

module cpu_top
(
    input           Clk,
    input           async_rst,

    // uart
    input           usb_uart_rxd,
    output          usb_uart_txd,
    output [7:0]    SevenSegment,
    output [3:0]    Enable
);

wire        sys_clk;
wire        cp0_clk;
reg         rst;
reg  [5 :0] sync_rst_sr;
wire [31:0] cp0_mem_addr;
wire [31:0] cp0_wr_data;
wire        cp0_wr_enable;


clk_wiz_0 cpu_clock_gen(
    .clk_in1  (Clk),
    .clk_out1 (cp0_clk)
);


// ====================================================================
// |                         YOUR CPU CORE HERE                       |
// ====================================================================

PipelineCPU 
CPU_core(
    .clk           (cp0_clk),
    .start         (~rst),
    .cp0_mem_addr  (cp0_mem_addr ),
    .cp0_wr_data   (cp0_wr_data  ),
    .cp0_wr_enable (cp0_wr_enable)
);

// ====================================================================



// Modify the parameter inside uart_tx module for different clock configurations.
uart_tx
uart_tx_inst(
    .i_Clock     (cp0_clk),
    .i_Tx_DV     (cp0_wr_enable & (cp0_mem_addr[31:28] == 4'hA)),
    .i_Tx_Byte   (cp0_wr_data[7:0]),
    .o_Tx_Active (),
    .o_Tx_Serial (usb_uart_txd)
);


// ====================================================================
// |        "DebugSevenSegment", "RunningSevenSegment" and            |
// |        "SevenSegMux" are modules for debugging on FPGA.          |
// |        You may comment out them for faster synthesis.            |
// ====================================================================

wire [7:0] seg_digit_0;
wire [7:0] seg_digit_1;
wire [7:0] seg_digit_2;
wire [7:0] seg_digit_3;

DebugSevenSegment debug_digit_012(
    .Clk         (cp0_clk),
    .reset       (rst),
    .data_in     (cp0_wr_data),
    .addr_in     (cp0_mem_addr),
    .addr_enable (cp0_mem_addr[31:28] == 4'hB),
    .wr_enable   (cp0_wr_enable),
    .seg_digit_0 (seg_digit_0),
    .seg_digit_1 (seg_digit_1),
    .seg_digit_2 (seg_digit_2)
);

// Cool running 7-segment for your own use.
// assert "Disable" for 1 cycle to stop it from running.
RunningSevenSegment debug_digit_3(
    .Clk          (cp0_clk),
    .Reset        (rst),
    .Disable      (0),
    .SevenSegment (seg_digit_3)  
);

//                         (SYSTEM CLK  / refresh rate (in Hz) )
SevenSegMux #(.REFRESH_RATE(20_000_000 / 320))
seg_mux(
    .Clk         (cp0_clk),
    .reset       (async_rst),
    .seg_digit_0 (seg_digit_0),
    .seg_digit_1 (seg_digit_1),
    .seg_digit_2 (seg_digit_2),
    .seg_digit_3 (seg_digit_3),
    
    .seg_out     (SevenSegment),
    .seg_enable  (Enable)
);


always @(posedge cp0_clk) begin
    if (async_rst) begin
        sync_rst_sr <= 6'b111_111;
    end
    else begin
        sync_rst_sr <= (sync_rst_sr << 1);
    end
end

always @(posedge cp0_clk) begin
    rst <= sync_rst_sr[5];
end




endmodule
