
module bc_4bit(input en,
					input clear,
			      input clk,
					output reg[3:0] out
	);

	reg carry;
	
	// No load functionality of the binary counter
	// assume initially it is zero
	initial begin
		out = 3'b0000;
	end

	always @(posedge clk, posedge clear)
	begin
		if(en)
		begin
			// Clear bit is set set to zero
			if(clear)
			begin
				out = 3'b0000;
			end
			// Only operate if clear bit is not set
			else
			begin
				// Single add statement opeartion encapsulates the counter logic
				out = out + 1'b1; 
			end
		end
	end
	
endmodule