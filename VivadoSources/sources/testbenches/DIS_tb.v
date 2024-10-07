`timescale 1ns/1ps
module DIS_tb ();

    reg clk = 1'b0;
    reg tog = 1'b0;
    reg [15:0] in = 16'b0;
    wire [1:0] enbar;
    wire [6:0] seg1;
    wire [6:0] seg2;
    wire [6:0] seg3;

    always #4 clk <= ~clk;

    initial begin
        #69 in <= 16'd1234;
        #69 in <= 16'd6969;
        #69 in <= 16'd42069;
        #69 in <= 16'hfaaa;
        #30 tog <= 1'b1;
    end

    DIS dut (
        .CLK(clk),
        .TOG(tog),
        .IN(in),
        .ENBAR(enbar),
        .SEG1(seg1),
        .SEG2(seg2),
        .SEG3(seg3)
    );

endmodule