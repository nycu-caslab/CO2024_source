// `timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 02/17/2024 09:30:59 AM
// Design Name: 
// Module Name: LUTRAM
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


module LUTRAM #(XLEN = 32, ADDR_WIDTH = 32, DATA_ENTRY = 256)
(
    input                   clk,
    input  [ADDR_WIDTH-1:0] addr,
    input  [XLEN-1:0]       data_in,
    input                   we,
    output [XLEN-1:0]       data_out
);

(*ram_style = "distributed"*) reg [XLEN-1:0] LUTRAM [DATA_ENTRY-1:0];
wire [31:0] route_in;
wire [31:0] route_out;

initial begin
    $readmemb("MEMORY_PRELOAD.mem", LUTRAM);
end

assign route_in = {data_in[7:0], data_in[15:8], data_in[23:16], data_in[31:24]};

always @(posedge clk) begin
    if (we) begin
        LUTRAM[addr] <= route_in;
    end
end

assign route_out = LUTRAM[addr];


assign data_out[31:24] = route_out[7 :0 ];
assign data_out[23:16] = route_out[15:8 ];
assign data_out[15:8 ] = route_out[23:16];
assign data_out[7 :0 ] = route_out[31:24];

endmodule
