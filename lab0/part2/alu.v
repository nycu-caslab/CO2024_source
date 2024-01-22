module alu(
    input signed [3:0] a,
    input signed [3:0] b,
    input [2:0] s,
    output reg signed [3:0] y
); 
    // alu has two input operand a and b.
    // It executes different operation over input a and b based on input s
    // then generate result to output y
    
    // TODO: implement your 4bits ALU design here and using your own fulladder module in this module
    // For testbench verifying, do not modify input and output pin
    
endmodule

