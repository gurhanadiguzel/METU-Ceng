`timescale 1ns / 1ps
module testbench_bc;

	// Inputs
	reg en;
	reg clk;
	reg clear;
	// Outputs
	wire[3:0] Q;

	// Instantiate the Unit Under Test (UUT)
	bc_4bit uut (.en(en), 
					 .clear(clear),
					 .clk(clk),
					 .out(Q));

	// At 5, 15, 25, .. clk will change 1->0
	// At 10, 20, 30, .. clk will change 0->1
   initial clk = 1;
	initial clear = 0;
	initial en = 0;
	
	always #5 clk = ~clk;

	initial begin
		// You can set the monitor aslo (this is commented out)
		// Monitor outputs everytime a signal is changed
		// Since we specifically display Q everytime we dont use it
		// in this case
		//$monitor("Time=%.2d | Q=%b en=%b ", $time, Q, en);
        		
		#1; //(1ns)Check Initial Q value (Should be zero)
		$display("Q=%b", Q);
      
		#10; //(11ns) Counter is not enabled Q still should be zero
		$display("Q=%b", Q);
		
		#1; //(12ns) Set the enable bit, now counter should work
		en = 1'b1;
		
		#9; //(21ns) Now it should be one
		$display("Q=%b", Q);// 1
		// Normal counter work
		#10;
		$display("Q=%b", Q);// 2
		#10;
		$display("Q=%b", Q);// 3
		#10;
		$display("Q=%b", Q);// 4
		#10;
		$display("Q=%b", Q);// 5
		#10;
		$display("Q=%b", Q);// 6
		#10;
		$display("Q=%b", Q);// 7
		#10;
		$display("Q=%b", Q);// 8
		#10;
		$display("Q=%b", Q);// 9
		#10;
		$display("Q=%b", Q);// 10
		#10;
		$display("Q=%b", Q);// 11
		#40;
		$display("Q=%b", Q);// 15
		#10;
		$display("Q=%b", Q);// 16 (should be zero)
		#20;
		$display("Q=%b", Q);// 2
		// Trigger a clear
		#1; //(192ns)
		clear = 1'b1;
		#1;
		clear = 1'b0;
		// Here Q should be zero
		$display("Q=%b", Q);
		#8;
		$display("Q=%b", Q);
		#10;
		$display("Q=%b", Q);
		// All Done!
		$finish;

	end
      
endmodule
