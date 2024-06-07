module InstructionMemory 
(
    input clk,
    input [31:0] readAddr,
    output [31:0] inst
);


LUTRAM #(.XLEN(32), .ADDR_WIDTH(10), .DATA_ENTRY(1024))
i_memory
(
    .clk(clk),
    .addr(readAddr[11:2]),
    .data_in(0),
    .we(0),
    .data_out(inst)
); 



endmodule
