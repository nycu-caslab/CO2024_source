module SingleCycleCPU (
    input clk,
    input start,
    output signed [31:0] t0,
    output signed [31:0] t1,
    output signed [31:0] t2,
    output signed [31:0] t3,
    output signed [31:0] t4,
    output signed [31:0] t5,
    output signed [31:0] t6,
    output signed [31:0] s0,
    output signed [31:0] s1,
    output signed [31:0] s2,
    output signed [31:0] sp
);

// TODO: connect wire to realize SingleCycleCPU
// The following provides simple template,
// you can modify it as you wish except I/O pin and register module

PC m_PC(
    .clk(),
    .rst(),
    .pc_i(),
    .pc_o()
);

Adder m_Adder_1(
    .a(),
    .b(),
    .sum()
);

InstructionMemory m_InstMem(
    .readAddr(),
    .inst()
);

Control m_Control(
    .opcode(),
    .branch(),
    .memRead(),
    .memtoReg(),
    .ALUOp(),
    .memWrite(),
    .ALUSrc(),
    .regWrite()
);

// For Student: 
// Do not change the Register instance name!
// Or you will fail validation.

Register m_Register(
    .clk(),
    .rst(),
    .regWrite(),
    .readReg1(),
    .readReg2(),
    .writeReg(),
    .writeData(),
    .readData1(),
    .readData2()
);

// ======= for validation ======= 
// == Dont change this section ==
assign t0 = m_Register.regs[5];
assign t1 = m_Register.regs[6];
assign t2 = m_Register.regs[7];
assign s0 = m_Register.regs[8];
assign s1 = m_Register.regs[9];
assign s2 = m_Register.regs[18];
assign t3 = m_Register.regs[28];
assign t4 = m_Register.regs[29];
assign t5 = m_Register.regs[30];
assign t6 = m_Register.regs[31];
assign sp = m_Register.regs[2];
// ======= for vaildation =======

ImmGen m_ImmGen(
    .inst(),
    .imm()
);

ShiftLeftOne m_ShiftLeftOne(
    .i(),
    .o()
);

Adder m_Adder_2(
    .a(),
    .b(),
    .sum()
);

Mux2to1 #(.size(32)) m_Mux_PC(
    .sel(),
    .s0(),
    .s1(),
    .out()
);

Mux2to1 #(.size(32)) m_Mux_ALU(
    .sel(),
    .s0(),
    .s1(),
    .out()
);

ALUCtrl m_ALUCtrl(
    .ALUOp(),
    .funct7(),
    .funct3(),
    .ALUCtl()
);

ALU m_ALU(
    .ALUctl(),
    .A(),
    .B(),
    .ALUOut(),
    .zero()
);

DataMemory m_DataMemory(
    .rst(),
    .clk(),
    .memWrite(),
    .memRead(),
    .address(),
    .writeData(),
    .readData()
);

Mux2to1 #(.size(32)) m_Mux_WriteData(
    .sel(),
    .s0(),
    .s1(),
    .out()
);

endmodule
