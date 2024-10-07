module MU (
    input CLK,
    input WEBAR,
    input [15:0] A,
    input [15:0] WD,
    output [15:0] RD
);

    reg [15:0] mem[$rtoi($pow(2,16))-1:0]; // memory

    assign RD = WEBAR ? mem[A] : 16'bz;

    always@(posedge CLK) begin
        if (~WEBAR) begin
           mem[A] <= WD; 
        end
    end

endmodule