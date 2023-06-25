`timescale 1ns / 1ps
module lab4ROM (input [3:0] romAddr, output reg[4:0] romOutput);
/*Write your code here*/
 reg [4:0]rom [0:15];
  
  initial begin	
  	rom[4'b0000]= 5'b00000;
	rom[4'b0001]= 5'b00001;
  	rom[4'b0010]= 5'b00110;
    rom[4'b0011]= 5'b00111;
    rom[4'b0100]= 5'b01011;
    rom[4'b0101]= 5'b01100;
    rom[4'b0110]= 5'b01101;
    rom[4'b0111]= 5'b01110;
    rom[4'b1000]= 5'b11101;
    rom[4'b1001]= 5'b11110;
	rom[4'b1010]= 5'b11111;
    rom[4'b1011]= 5'b10000;
    rom[4'b1100]= 5'b10111;
    rom[4'b1101]= 5'b11000;
    rom[4'b1110]= 5'b11001;
    rom[4'b1111]= 5'b11010;
  end
	
always@(*)
	begin
      romOutput = rom[romAddr];
    end
endmodule
																							
module lab4RAM (
	input ramMode, //0:read, 1:write
	input [3:0] ramAddr, 
	input [4:0] ramInput,
	input  ramOp, //0:polynomial, 1:derivative
	input [1:0] ramArg,  //00:+1, 01:+2, 10:-1, 11:-2
	input CLK, 
	output reg [8:0] ramOutput);

/*Write your code here*/
	initial ramOutput = 0;  
	integer x;
  	reg[7:0] bin;
	reg [8:0]ram [0:15];

	always@(*)
		if(ramMode == 1'b0)
			begin
				ramOutput = ram[ramAddr]; 
			end
		

	always @(posedge CLK)    
	begin     
		if(ramMode == 1'b1)
			begin
              	bin = 0;
				case(ramArg)
					2'b00: x = 1;
					2'b01: x = 2;
					2'b10: x = -1;
					2'b11: x = -2;
				endcase
				if(ramOp == 0)
				begin
                  if (ramInput[4]==0) bin = bin + x**4; 
                  else if (ramInput[4] == 1) bin = bin -x**4;
                  if (ramInput[3]==0) bin = bin + x**3;
                  else if (ramInput[3] == 1) bin = bin -x**3;
                  if (ramInput[2]==0) bin = bin + x**2;
                  else if (ramInput[2] == 1) bin = bin -x**2;
                  if (ramInput[1]==0) bin = bin + x;
                  else if (ramInput[1] == 1) bin = bin -x;
                  if (ramInput[0]==0) bin = bin + 1;
                  else if (ramInput[0] == 1) bin = bin -1;
				end
              
				else if(ramOp == 1)
				begin 
                  if (ramInput[4]==0) bin = bin + 4*x**3;
                  else if (ramInput[4] == 1) bin = bin -4*x**3;
                  if (ramInput[3]==0) bin = bin + 3*x**2;
                  else if (ramInput[3] == 1) bin = bin - 3*x**2;
                  if (ramInput[2]==0) bin = bin + 2*x;
                  else if (ramInput[2] == 1) bin = bin -2*x;
                  if (ramInput[1]==0) bin = bin + 1;
                  else if (ramInput[1] == 1) bin = bin -1;
				end

				if(bin[7] == 1'b1) ram[ramAddr] = {1'b1,-bin};
				else if (bin[7] == 1'b0) ram[ramAddr] = {1'b0,bin};  
			end
		end
endmodule


module polMEM(input mode, input [3:0] memAddr, input op, input [1:0] arg, input CLK, output wire [8:0] memOutput);

	/*Don't edit this module*/
	wire [4:0]  romOutput;

	lab4ROM RO(memAddr, romOutput);
	lab4RAM RA(mode, memAddr, romOutput, op, arg, CLK, memOutput);
	
endmodule



