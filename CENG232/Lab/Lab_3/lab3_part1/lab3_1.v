`timescale 1ns / 1ps

module ab(input A, input B, input clk, output reg Q);
    initial Q = 0;
    always @ (posedge clk)
      if(A == 0 & B == 0)
        begin
          Q <= Q;
        end
      else if(A == 1 && B == 0)
        begin
          Q <= 0;
        end
      else if(A == 0 & B == 1)
        begin
          Q <= 1;
        end
      else if(A == 1 & B == 1)
        begin
          Q <= ~Q;
        end
endmodule

module ic1337(// Inputs
               input I0,
               input I1,
               input I2,
               input clk,
               // Outputs
               output Q0,
               output Q1,
               output Z);
	 
     wire A;
     wire B;

     assign A = ~(I0 | ~I1) && ~I2;
     assign B = ~(I2 | ~I1) ~^ I0; 

     ab g1(A,I2,clk,Q0);
	   ab g2(~I2,B,clk,Q1);

     assign Z = Q0 ^ Q1; 

endmodule