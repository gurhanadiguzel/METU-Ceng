`timescale 1ns / 1ps

module lab4_2(// INPUTS
              input wire      mode,
              input wire[2:0] opCode,
              input wire[3:0] value,
              input clk,
              input reset,
              // OUTPUTS
              output reg[9:0] result,
              output reg cacheFull,
              output reg invalidOp,
              output reg overflow);

    reg[9:0] prev;
    reg[9:0] temp;
    reg[3:0] code;
    reg [2:0] loadList [0:31];
    reg [3:0] valueList [0:31];
	integer count ;
    integer exec ;
    integer index;
    integer resultint;  
    integer value1;  

    initial begin
        cacheFull = 0;
        invalidOp = 0;
        overflow = 0;
        result = 0;
        count=0;
        exec=0;
        index=0; 
    end
    
    always @(posedge clk or posedge reset)
    begin
		if (reset)
		begin 
            cacheFull = 0;
            invalidOp = 0;
            overflow = 0;
            result = 0;
            prev = 0;
            temp = 0;
            count = 0;
            exec = 0;
            index = 0;  	  
		end
			
		else
		begin 
			if(mode == 0)
            begin
                if(count >= 32) 
                begin 
                    cacheFull=1;
                end 

                else if({opCode[2],opCode[1],opCode[0]} == 3'b111 || {opCode[2],opCode[1],opCode[0]} == 3'b011)
                begin
                    invalidOp = 1;
                end

                else 
                begin   
                    loadList[count]= opCode;                                        
                    valueList[count] = value;
                    count=count+1;
                    invalidOp = 0;
                end
            end

            else if(mode == 1 && count !=0)
            begin
                overflow = 0;
                invalidOp = 0;                
                temp = result;
                value1 = valueList[exec];
                code = loadList[exec];
                if(code == 3'b000) begin result = result+value1; resultint = resultint +value1; end
                else if(code == 3'b001) begin result=result+prev+value1; resultint=resultint +prev+value1; end
                else if(code == 3'b010) begin result=result*prev+value1; resultint =resultint *prev+value1; end
                else if(code == 3'b100) begin result = result[0]+result[1]+result[2]+result[3]+result[4]+result[5]+result[6]+result[7]+result[8]+result[9]; resultint = result; end
                else if(code == 3'b101) begin result = {result[0],result[1],result[2],result[3],result[4],result[5],result[6],result[7],result[8],result[9]}; resultint = result; end
                else if(code == 3'b110) begin index = value1; temp = prev; end
                if(resultint >=1024) begin overflow = 1; end
                resultint = result;
                exec=exec+1;
                prev=temp;      
                if(count<=exec) begin exec=index;end             
            end         
	    end
    end
endmodule