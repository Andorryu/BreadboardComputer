module DIS (
    input CLK, // fpga's clk
    input TOG, // fpga's button - 1 means negative, 0 means positive
    input [15:0] IN, // binary number to drive 7-seg
    output reg [1:0] ENBAR = 2'b01, // used to enable all six 7-seg displays
    output reg [6:0] SEG1 = 7'h7f, // inputs A-G on the 7-seg display where SEG[0] = A and SEG[6] = G, these are active low
    output reg [6:0] SEG2 = 7'h7f,
    output reg [6:0] SEG3 = 7'h7f
);

    wire [6:0] curSegs[5:0]; // current digits on A-G are stored here
    reg counter = 1'b0;

    wire [6:0] seglut[0:9]; // holds the digits on 7-seg for 0-9
    assign seglut[0] = 7'b1000000;
    assign seglut[1] = 7'b1111001;
    assign seglut[2] = 7'b0100100;
    assign seglut[3] = 7'b0110000;
    assign seglut[4] = 7'b0011001;
    assign seglut[5] = 7'b0010010;
    assign seglut[6] = 7'b0000010;
    assign seglut[7] = 7'b1111000;
    assign seglut[8] = 7'b0000000;
    assign seglut[9] = 7'b0010000;
    wire [6:0] minus = 7'b0111111;
    wire [6:0] off = 7'b1111111;

    always @(posedge CLK) begin
        // update counter
        counter = ~counter;
        // output a digit
        SEG1 = curSegs[counter];
        SEG2 = curSegs[counter+2];
        SEG3 = curSegs[counter+4];
        // enable the correct digit
        ENBAR = ENBAR << 1;
        if (ENBAR == 0)
            ENBAR = 1;
    end

    // set curSegs according to DIS
    wire [15:0] mag = TOG && IN[15] ? (~IN) + 1 : IN;
    wire [5:0] signPlace = mag < 10 ? 6'b000010 :
                          mag < 100 ? 6'b000100 :
                         mag < 1000 ? 6'b001000 :
                        mag < 10000 ? 6'b010000 :
                                      6'b100000 ;

    assign curSegs[0] = seglut[mag % 10];
    assign curSegs[1] = (mag/10) > 0 ? seglut[(mag/10) % 10] :
                 TOG && IN[15] && signPlace[1] ? minus : off;
    assign curSegs[2] = (mag/100) > 0 ? seglut[(mag/100) % 10] :
                 TOG && IN[15] && signPlace[2] ? minus : off;
    assign curSegs[3] = (mag/1000) > 0 ? seglut[(mag/1000) % 10] :
                 TOG && IN[15] && signPlace[3] ? minus : off;
    assign curSegs[4] = (mag/10000) > 0 ? seglut[(mag/10000) % 10] :
                 TOG && IN[15] && signPlace[4] ? minus : off;
    assign curSegs[5] = TOG && IN[15] && signPlace[5] ? minus : off;

endmodule