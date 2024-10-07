`timescale 1ns/1ps
module PC_tb ();

    reg clk = 1'b0;
    reg clrbar = 1'b0;
    reg [15:0] d = 16'b0;
    wire [15:0] q;

    PC dut (
        .CLK(clk),
        .CLRBAR(clrbar),
        .D(d),
        .Q(q)
    );

    initial begin
        #1 clrbar = 1'b1;
        #13 d <= 16'hffff;
        #13 d <= 16'habcd;
        #13 d <= 16'h107f;
        #13 d <= 16'h1010;
        #13 d <= 16'h538d;
        #13 d <= 16'hc6f0;
        #13 d <= 16'hbccc;
        #10 clrbar = 0'b0;
        #13 d <= 16'h538d;
        #13 d <= 16'hc6f0;
        #13 d <= 16'hbccc;
    end

    always begin
        #15 clk <= ~clk;
    end
endmodule