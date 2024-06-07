`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 05/16/2024 01:01:44 PM
// Design Name: 
// Module Name: SevenSegMux
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


module SevenSegMux
#( 
    parameter [25:0] REFRESH_RATE = 0 
)
(
    input       Clk,
    input       reset,
    input [7:0] seg_digit_0,
    input [7:0] seg_digit_1,
    input [7:0] seg_digit_2,
    input [7:0] seg_digit_3,

    output reg [7:0] seg_out,
    output reg [3:0] seg_enable
);

reg [3:0] SR;

reg [25:0] counter;

always @(posedge Clk or posedge reset) begin
    if (reset) begin
        counter <= 0;
        SR <= 4'b1110;      // 100 MHz / Hz =
    end 
    else begin
        if (counter == REFRESH_RATE) begin
            counter <= 0;
            SR <= {SR[2:0], SR[3]};
        end
        else begin
            SR <= SR;
            counter <= counter + 1;
        end
    end
end



always @(*) begin
    case (SR)
        4'b1110: begin
            seg_out = seg_digit_0;
            seg_enable = 4'b1110;
        end
        4'b1101: begin
            seg_out = seg_digit_1;
            seg_enable = 4'b1101;
        end
        4'b1011: begin
            seg_out = seg_digit_2;
            seg_enable = 4'b1011;
        end
        4'b0111: begin
            seg_out = seg_digit_3;
            seg_enable = 4'b0111;
        end
        default: begin
            seg_out = 8'b0000_0000;
            seg_enable = 4'b0000;
        end
    endcase
end

endmodule
