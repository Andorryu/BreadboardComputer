module ALU (
    input [15:0] A,
    input [15:0] B,
    input [3:0] SHAMT,
    input [1:0] OP,
    input SUB,
    input ARI,
    input LEF,
    output [15:0] C,
    output ZERO
);

    assign C = OP == 2'd0 ? (SUB ? A - B : A + B) :
               OP == 2'd1 ? (~(A & B)) :
               OP == 2'd2 ? (A < B ? 16'h0001 : 16'h0000) :
               OP == 2'd3 ? (LEF ? C << SHAMT : ARI ? C >> SHAMT : C >> SHAMT) :
               16'bx;

    assign ZERO = C == 16'b0;

endmodule