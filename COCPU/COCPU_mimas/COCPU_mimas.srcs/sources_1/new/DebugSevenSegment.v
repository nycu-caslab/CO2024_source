`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 05/16/2024 12:36:57 PM
// Design Name: 
// Module Name: StatusSevenSegment
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


module DebugSevenSegment(
    input        Clk,
    input        reset,
    input [31:0] data_in,
    input [31:0] addr_in,
    input        addr_enable,
    input        wr_enable,

    output reg [7:0] seg_digit_0,
    output reg [7:0] seg_digit_1,
    output reg [7:0] seg_digit_2
);

localparam [3:0] S_RST  = 0;
localparam [3:0] S_LW_TST = 1;
localparam [3:0] S_RUN  = 2;
localparam [3:0] S_END  = 3;

localparam [3:0] S_ERR_LW = 4;


//        a    
//      ____
//   f |    | b
//     |_g__| 
//   e |    | c
//     |____| .h
//       d
// 7-segment display
//                          abcd_efgh
localparam [7:0] SEG_R = 8'b1111_0101;
localparam [7:0] SEG_S = 8'b0100_1001;
localparam [7:0] SEG_T = 8'b1110_0001;
localparam [7:0] SEG_U = 8'b1000_0011;
localparam [7:0] SEG_N = 8'b0001_0011;
localparam [7:0] SEG_E = 8'b0110_0001;
localparam [7:0] SEG_D = 8'b1000_0101;
localparam [7:0] SEG_0 = 8'b0000_0011;
localparam [7:0] SEG_1 = 8'b1001_1111;

reg [3:0] P;
reg [3:0] P_next;


always @(*) begin
    P_next = P;
    case(P)
        S_RST: begin
            P_next = S_LW_TST;
        end
        S_LW_TST: begin
            if (addr_enable & wr_enable) begin
                if (addr_in != data_in) begin
                    P_next = S_ERR_LW;
                end
                else if (addr_in[31:24] == 8'hBF) begin
                    P_next = S_RUN;
                end
            end
        end
        S_RUN: begin
            if (addr_enable & wr_enable) begin
                if(data_in[3:0] == 4'h2) begin
                    P_next = S_END;
                end
            end
        end
        S_END: begin
            P_next = S_END;
        end
    endcase
end

always @(posedge Clk or posedge reset) begin
    if(reset) begin
        P <= S_RST;
    end else begin
        P <= P_next;
    end
end

always @(*) begin
    case(P)
        S_RST: begin
            seg_digit_0 = SEG_R;
            seg_digit_1 = SEG_S;
            seg_digit_2 = SEG_T;
        end
        S_RUN: begin
            seg_digit_0 = SEG_R;
            seg_digit_1 = SEG_U;
            seg_digit_2 = SEG_N;
        end
        S_END: begin
            seg_digit_0 = SEG_E;
            seg_digit_1 = SEG_N;
            seg_digit_2 = SEG_D;
        end
        S_LW_TST: begin
            seg_digit_0 = SEG_T;
            seg_digit_1 = SEG_0;
            seg_digit_2 = SEG_1;
        end
        S_ERR_LW: begin
            seg_digit_0 = SEG_E;
            seg_digit_1 = SEG_0;
            seg_digit_2 = SEG_1;
        end
        default: begin
            seg_digit_0 = SEG_0;
            seg_digit_1 = SEG_0;
            seg_digit_2 = SEG_0;
        end
    endcase
end



endmodule
