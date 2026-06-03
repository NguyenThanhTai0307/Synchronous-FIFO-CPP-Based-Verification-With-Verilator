`ifndef DESIGN_SV
`define DESIGN_SV
module sync_fifo #(
    parameter WIDTH = 8,
    parameter DEPTH = 8
)

(
    input clk, rstn,
    input wr_en, rd_en,
    input [WIDTH - 1 : 0] din,
    output reg [WIDTH - 1 : 0] dout,
    output full, empty
);

  reg [$clog2(DEPTH) - 1 : 0] wr_pt = 0;
  reg [$clog2(DEPTH) - 1 : 0] rd_pt = 0;
  reg [$clog2(DEPTH) : 0] count = 0;

reg [WIDTH - 1 : 0] fifo [DEPTH];

always @(posedge clk) begin
    if (!rstn) begin
        count <= 0;
        wr_pt <= 0;
        rd_pt <= 0;
    end 
    else begin
        // Handle Pointer Increments independently
        if (wr_en && !full)  begin
          fifo[wr_pt] <= din; 
          wr_pt <= wr_pt + 1;
        end
        if (rd_en && !empty) begin
          dout <= fifo[rd_pt];
          rd_pt <= rd_pt + 1;
        end
        // Unified Count Logic
        case ({wr_en && !full, rd_en && !empty})
            2'b10: count <= count + 1; // Write only
            2'b01: count <= count - 1; // Read only
            2'b11: count <= count;     // Read + Write = No change
            default: count <= count;   // No change
        endcase
    end
end

//full and emty assignment
  assign full = (count == DEPTH);
assign empty = (count == 0);

endmodule
`endif // DESIGN_SV