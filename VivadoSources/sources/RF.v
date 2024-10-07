module RF (
    input CLK,
    input RSTBAR,
    input WEBAR,
    input [3:0] RA1,
    input [3:0] RA2,
    input [3:0] WA,
    input [15:0] WD,
    output [15:0] RD1,
    output [15:0] RD2,
    output [15:0] DIS
);

    reg [15:0] regFile[15:1];

    assign DIS = regFile[15];
    assign RD1 = RA1 == 4'b0 ? 16'b0
                      : regFile[RA1];
    assign RD2 = RA2 == 4'b0 ? 16'b0
                      : regFile[RA2];

    always @(posedge CLK, negedge RSTBAR) begin
        if (!RSTBAR) begin
            regFile[14] <= 16'b0;
            regFile[15] <= 16'b0;
        end
        else if (CLK && !WEBAR && WA != 4'b0)
            regFile[WA] <= WD;
    end

endmodule