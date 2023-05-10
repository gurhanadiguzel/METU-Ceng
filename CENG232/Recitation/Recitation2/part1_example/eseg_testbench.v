
module testBench;
	 reg A;
    reg B;
    reg C;
    reg D;
    wire eSeg;

	binary_to_eseg INSTANCE(A, B, C, D, eSeg);

initial
		begin
			$monitor($time,,,
				"A=%b B=%b C=%b D=%b eSeg=%b",
				A,B,C,D,eSeg);

			// waveform for simulating binary_to_eseg instance
			#10; //10
			$display("Setting all inputs to 0");
			A=0; B=0; C=0; D=0;

			#10; //20
			$display("Setting D to 1");
			D=1;
			
			#10; //30
			$display("Setting C to 1, D to 0");
			C=1; D=0;
			
			#10; //40
			$display("Ending simulation");
			$finish;
		end

endmodule


