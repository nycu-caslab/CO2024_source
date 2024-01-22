/*
*  Description:
*   - fullAdder compute addition of input cin, a and b.
*   - Then output result to s and carry bit to cout
*/

module fullAdder(input cin, input a, input b, output s, output cout);

    // TODO: implement your fullAdder design here
    // For testbench verifying, do not modify input and output pin
    wire [1:0] sum = a + b + cin;
    assign cout = sum[1];
    assign s = sum[0];
endmodule

