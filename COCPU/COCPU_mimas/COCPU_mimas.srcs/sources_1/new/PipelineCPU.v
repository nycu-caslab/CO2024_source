module PipelineCPU (
    input         clk,
    input         start,
    output [31:0] cp0_mem_addr,
    output [31:0] cp0_wr_data,
    output        cp0_wr_enable    
);




InstructionMemory instMemory
(
    .clk(clk),
    .readAddr(),
    .inst()
);


Register register(
    .clk(clk),
    .rst(start),
    .regWrite(),
    .readReg1(),
    .readReg2(),
    .writeReg(),
    .writeData(),
    .readData1(),
    .readData2()
);



DataMemory dataMemory(
    .clk(clk),
    .memWrite(),
    .memRead(),
    .address(),
    .writeData(),
    .readData()
);






endmodule