module DataMemory(
	input lbu,
	input clk,
	input memWrite,
	input memRead,
	input [31:0] address,
	input [31:0] writeData,
	output reg [31:0] readData
);

wire [31:0] rd_buf;
always @(*) begin
	if (lbu) begin
		case (address[1:0])
			2'b11: readData = {8'b0   ,8'b0   ,8'b0   ,rd_buf[31:24]};
			2'b10: readData = {8'b0   ,8'b0   ,8'b0   ,rd_buf[23:16]};
			2'b01: readData = {8'b0   ,8'b0   ,8'b0   ,rd_buf[15:8 ]};
			2'b00: readData = {8'b0   ,8'b0   ,8'b0   ,rd_buf[7:0  ]};
		endcase
	end
	else if (memRead) begin
		readData = rd_buf;
	end
	else begin
		readData = 0;
	end
end

LUTRAM #(.XLEN(32), .ADDR_WIDTH(10), .DATA_ENTRY(1024))
d_memory
(
    .clk(clk),
    .addr(address[11:2]),
    .data_in(writeData),
    .we(memWrite),
    .data_out(rd_buf)
); 



endmodule
