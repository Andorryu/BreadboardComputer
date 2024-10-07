module PC (
    input wire CLK, CLRBAR,
    input wire [15:0] D,
    output reg [15:0] Q);
    
    always @(posedge CLK, negedge CLRBAR)
        if (~CLRBAR)
            Q <= 16'h0000;
        else
            Q <= D;
        
endmodule