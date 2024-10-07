`timescale 1ns/1ps

module RF_tb ();

    reg clk = 1'b0;
    reg rstbar;
    reg webar;
    reg [3:0] ra1 = 4'b0;
    reg [3:0] ra2 = 4'b0;
    reg [3:0] wa = 4'b0;
    reg [15:0] wd = 16'b0;
    wire [15:0] rd1;
    wire [15:0] rd2;
    wire [15:0] dis;

    always #4 clk <= ~clk;

    initial begin
        webar <= 1'b1; rstbar <= 1'b1;
        #8 rstbar <= 1'b0;
        #3 rstbar <= 1'b1;
        // write 20 to R1 and read from R1 using read port 1
        #3 webar <= 1'b0; wa <= 4'd1; wd <= 16'd20; ra1 <= 4'd1;
        #8 ra2 <= 4'd1;
        #3 ra1 <= 4'd15;
        #3 ra1 <= 4'd14;
        #3 ra1 <= 4'd8;
        // write 31884 to R8
        #3 webar <= 1'b0; wa <= 4'd8; wd <= 16'd31884;
        // write 2222 to R8
        #8 wa <= 4'd15; wd <= 16'd2222;
        // write 10943 to R8
        #8 wa <= 4'd14; wd <= 16'd10943; ra2 <= 4'd14;
        #8 webar <= 1'b1;
        #3 rstbar <= 1'b0;
        #3 rstbar <= 1'b1;
    end

    RF dut (
        .CLK(clk),
        .RSTBAR(rstbar),
        .WEBAR(webar),
        .RA1(ra1),
        .RA2(ra2),
        .WA(wa),
        .WD(wd),
        .RD1(rd1),
        .RD2(rd2),
        .DIS(dis)
    );

endmodule