module DataMemory(
	input rst,
	input clk,
	input memWrite,
	input memRead,
	input [31:0] address,
	input [31:0] writeData,
	output reg [31:0] readData
);
	// For Student: 
	// Do not modify this file!

	reg [7:0] data_memory [127:0];
	always @ (posedge clk, negedge rst) begin
		if(!rst) begin
			data_memory[0] <= 8'b0;
			data_memory[1] <= 8'b0;
			data_memory[2] <= 8'b0;
			data_memory[3] <= 8'b0;
			data_memory[4] <= 8'b0;
			data_memory[5] <= 8'b0;
			data_memory[6] <= 8'b0;
			data_memory[7] <= 8'b0;
			data_memory[8] <= 8'b0;
			data_memory[9] <= 8'b0;
			data_memory[10] <= 8'b0;
			data_memory[11] <= 8'b0;
			data_memory[12] <= 8'b0;
			data_memory[13] <= 8'b0;
			data_memory[14] <= 8'b0;
			data_memory[15] <= 8'b0;
			data_memory[16] <= 8'b0;
			data_memory[17] <= 8'b0;
			data_memory[18] <= 8'b0;
			data_memory[19] <= 8'b0;
			data_memory[20] <= 8'b0;
			data_memory[21] <= 8'b0;
			data_memory[22] <= 8'b0;
			data_memory[23] <= 8'b0;
			data_memory[24] <= 8'b0;
			data_memory[25] <= 8'b0;
			data_memory[26] <= 8'b0;
			data_memory[27] <= 8'b0;
			data_memory[28] <= 8'b0;
			data_memory[29] <= 8'b0;
			data_memory[30] <= 8'b0;
			data_memory[31] <= 8'b0;
			data_memory[32] <= 8'b0;
			data_memory[33] <= 8'b0;
			data_memory[34] <= 8'b0;
			data_memory[35] <= 8'b0;
			data_memory[36] <= 8'b0;
			data_memory[37] <= 8'b0;
			data_memory[38] <= 8'b0;
			data_memory[39] <= 8'b0;
			data_memory[40] <= 8'b0;
			data_memory[41] <= 8'b0;
			data_memory[42] <= 8'b0;
			data_memory[43] <= 8'b0;
			data_memory[44] <= 8'b0;
			data_memory[45] <= 8'b0;
			data_memory[46] <= 8'b0;
			data_memory[47] <= 8'b0;
			data_memory[48] <= 8'b0;
			data_memory[49] <= 8'b0;
			data_memory[50] <= 8'b0;
			data_memory[51] <= 8'b0;
			data_memory[52] <= 8'b0;
			data_memory[53] <= 8'b0;
			data_memory[54] <= 8'b0;
			data_memory[55] <= 8'b0;
			data_memory[56] <= 8'b0;
			data_memory[57] <= 8'b0;
			data_memory[58] <= 8'b0;
			data_memory[59] <= 8'b0;
			data_memory[60] <= 8'b0;
			data_memory[61] <= 8'b0;
			data_memory[62] <= 8'b0;
			data_memory[63] <= 8'b0;
			data_memory[64] <= 8'b0;
			data_memory[65] <= 8'b0;
			data_memory[66] <= 8'b0;
			data_memory[67] <= 8'b0;
			data_memory[68] <= 8'b0;
			data_memory[69] <= 8'b0;
			data_memory[70] <= 8'b0;
			data_memory[71] <= 8'b0;
			data_memory[72] <= 8'b0;
			data_memory[73] <= 8'b0;
			data_memory[74] <= 8'b0;
			data_memory[75] <= 8'b0;
			data_memory[76] <= 8'b0;
			data_memory[77] <= 8'b0;
			data_memory[78] <= 8'b0;
			data_memory[79] <= 8'b0;
			data_memory[80] <= 8'b0;
			data_memory[81] <= 8'b0;
			data_memory[82] <= 8'b0;
			data_memory[83] <= 8'b0;
			data_memory[84] <= 8'b0;
			data_memory[85] <= 8'b0;
			data_memory[86] <= 8'b0;
			data_memory[87] <= 8'b0;
			data_memory[88] <= 8'b0;
			data_memory[89] <= 8'b0;
			data_memory[90] <= 8'b0;
			data_memory[91] <= 8'b0;
			data_memory[92] <= 8'b0;
			data_memory[93] <= 8'b0;
			data_memory[94] <= 8'b0;
			data_memory[95] <= 8'b0;
			data_memory[96] <= 8'b0;
			data_memory[97] <= 8'b0;
			data_memory[98] <= 8'b0;
			data_memory[99] <= 8'b0;
			data_memory[100] <= 8'b0;
			data_memory[101] <= 8'b0;
			data_memory[102] <= 8'b0;
			data_memory[103] <= 8'b0;
			data_memory[104] <= 8'b0;
			data_memory[105] <= 8'b0;
			data_memory[106] <= 8'b0;
			data_memory[107] <= 8'b0;
			data_memory[108] <= 8'b0;
			data_memory[109] <= 8'b0;
			data_memory[110] <= 8'b0;
			data_memory[111] <= 8'b0;
			data_memory[112] <= 8'b0;
			data_memory[113] <= 8'b0;
			data_memory[114] <= 8'b0;
			data_memory[115] <= 8'b0;
			data_memory[116] <= 8'b0;
			data_memory[117] <= 8'b0;
			data_memory[118] <= 8'b0;
			data_memory[119] <= 8'b0;
			data_memory[120] <= 8'b0;
			data_memory[121] <= 8'b0;
			data_memory[122] <= 8'b0;
			data_memory[123] <= 8'b0;
			data_memory[124] <= 8'b0;
			data_memory[125] <= 8'b0;
			data_memory[126] <= 8'b0;
			data_memory[127] <= 8'b0;
		end
		else begin
			if(memWrite) begin
				/* verilator lint_off SYNCASYNCNET */
				data_memory[address + 3] <= writeData[31:24];
				data_memory[address + 2] <= writeData[23:16];
				data_memory[address + 1] <= writeData[15:8];
				data_memory[address]     <= writeData[7:0];
			end

			end
	end       

	always @(memRead, address) begin
		if(memRead) begin
			/* verilator lint_off SYNCASYNCNET */
			readData[31:24]   <= data_memory[address + 3];
			readData[23:16]   <= data_memory[address + 2];
			readData[15:8]    <= data_memory[address + 1];
			readData[7:0]     <= data_memory[address];
		end
	end

endmodule

