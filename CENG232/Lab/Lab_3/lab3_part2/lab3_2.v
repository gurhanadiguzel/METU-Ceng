`timescale 1ns / 1ps 
module lab3_2(
			input[4:0] smartCode,
			input CLK, 
			input lab, //0:Digital, 1:Mera
			input [1:0] mode, //00:exit, 01:enter, 1x: idle 
			output reg [5:0] numOfStuInMera,
			output reg [5:0] numOfStuInDigital,
			output reg restrictionWarnMera,//1:show warning, 0:do not show warning
			output reg isFullMera, //1:full, 0:not full
			output reg isEmptyMera, //1: empty, 0:not empty
			output reg unlockMera,	//1:door is open, 0:closed
			output reg restrictionWarnDigital,//1:show warning, 0:do not show warning
			output reg isFullDigital, //1:full, 0:not full
			output reg isEmptyDigital, //1: empty, 0:not empty
			output reg unlockDigital //1:door is open, 0:closed
	);
	 
	// You may declare your variables below	
	integer numberofOne,i;
	
	initial begin
			numOfStuInMera=0;
			numOfStuInDigital=0;
			restrictionWarnMera=0;
			isFullMera=0;
			isEmptyMera=1'b1;
			unlockMera=0;		
			restrictionWarnDigital=0;
			isFullDigital=0;
			isEmptyDigital=1'b1;
			unlockDigital=0;
	end

	//Modify the lines below to implement your design
	always @(posedge CLK)
	begin
		numberofOne = 0;
		for(i=0;i<5;i = i+1)
			if(smartCode[i] == 1'b1)
				numberofOne = numberofOne+1 ;
			
		restrictionWarnDigital = 0;
		restrictionWarnMera = 0;
		unlockDigital = 0;
		unlockMera = 0;

		if (mode == 2'b00)
			begin
				if (lab == 0 && isEmptyDigital != 1'b1)
					begin
						numOfStuInDigital = numOfStuInDigital-1;
						unlockDigital = 1;
					end
				else if ( lab == 1 && isEmptyDigital!= 1'b1 )
					begin
						numOfStuInMera = numOfStuInMera-1;
						unlockMera =1 ;
					end
			end
		else if (mode == 2'b01)
			begin
				if (lab == 0)
					begin
						if (numOfStuInDigital >= 30) 
							begin
							end 
						else if(numOfStuInDigital < 15)
							begin
								unlockDigital = 1;
								numOfStuInDigital = numOfStuInDigital+1;							
							end
						else if (numOfStuInDigital >= 15 && numberofOne%2 == 0)
							restrictionWarnDigital = 1;
						else 
							begin
								unlockDigital = 1;
								numOfStuInDigital = numOfStuInDigital+1;							
							end
					end
				else if ( lab == 1)
					begin
						if (numOfStuInMera >= 30) 
							begin
							end 
						else if(numOfStuInMera < 15)
							begin
								unlockMera = 1;
								numOfStuInMera = numOfStuInMera+1;							
							end
						else if (numOfStuInMera >= 15 && numberofOne%2 != 0)
							restrictionWarnMera = 1;
						else 
							begin
								unlockMera = 1;
								numOfStuInMera = numOfStuInMera+1;							
							end
					end
			end
		if(numOfStuInDigital == 0) isEmptyDigital = 1'b1;
		else isEmptyDigital = 1'b0;
		if(numOfStuInMera == 0) isEmptyMera = 1'b1; 
		else isEmptyMera = 1'b0;
		if(numOfStuInDigital == 30) isFullDigital = 1;
		else isFullDigital = 0;
		if(numOfStuInMera == 30) isFullMera = 1;
		else isFullMera = 0;
	end
endmodule