`timescale 1ns/1ps
module ALU_tb ();

    reg [15:0] a = 16'b0;
    reg [15:0] b = 16'b0;
    reg [3:0] shamt = 4'b0;
    reg [1:0] op = 2'b00;
    reg sub = 0;
    reg ari = 0;
    reg lef = 0;
    wire [15:0] c;
    wire zero;

    initial begin
        // add 53 + 69 = 122
        a <= 16'd53; b <= 16'd69; op <= 2'b00; #4
        // subtract 1938 - 7687 = -5749
        a <= 16'd1938; b <= 16'd7687; op <= 2'b00; sub <= 1'b1; #4
        // nand 010101 ~& 000111 = 111010
        a <= 16'b010101; b <= 16'b000111; op <= 2'b01; #4
        // slt -1 < 100 = 0
        a <= 16'hffff; b <= 16'd100; op <= 2'b10; #4
        // slt 4000 < 23345 = 0
        a <= 16'd4000; b <= 16'd23345; op <= 2'b10; #4
        // shift 010011 << 4 = 0100110000
        a <= 16'b010011; shamt <= 4'd4; ari <= 1'b0; lef <= 1'b1; op <= 2'b11; #4
        // shift 1000100010001000 >>> 6 = 1111111000100010
        a <= 16'b1000100010001000; shamt <= 4'd6; ari <= 1'b1; lef <= 1'b0; op <= 2'b11;
    end

    ALU dut (
        .A(a),
        .B(b),
        .SHAMT(shamt),
        .OP(op),
        .SUB(sub),
        .ARI(ari),
        .LEF(lef),
        .C(c),
        .ZERO(zero)
    );

endmodule