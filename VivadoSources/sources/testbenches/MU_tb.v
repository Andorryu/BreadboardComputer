`timescale 1ns/1ps
module MU_tb();

    reg clk = 1'b0;
    reg webar = 1'b1;
    reg [15:0] a = 16'b0;
    reg [15:0] wd = 16'b0;
    wire [15:0] rd;

    initial begin
    end

    always #3 clk <= ~clk;
    always begin
        #4 webar <= 1'b0;
        a <= a + 1;
        wd <= wd + 4;
        #4 webar <= 1'b1;
    end

    MU dut (
        .CLK(clk),
        .WEBAR(webar),
        .A(a),
        .WD(wd),
        .RD(rd)
    );

endmodule