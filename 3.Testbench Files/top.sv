`ifndef TOP_SV
`define TOP_SV

module top #(parameter WIDTH = 8,
             parameter DEPTH = 8
            ) (
                input clk,
                input rstn, 
                input wr_en,
                input rd_en,
                input [WIDTH - 1 : 0] din,
                output [WIDTH - 1 : 0] dout,
                output full,
                output empty
                );

    sync_fifo DUT (
        .clk (clk), .rstn (rstn),
        .rd_en (rd_en), .wr_en (wr_en),
      .full (full), .empty (empty),
      .din (din), .dout (dout)
    );

    bind sync_fifo Assertion #(
      .WIDTH(8), .DEPTH(8)) a0 
      (
      .clk (clk), .rstn (rstn),
      .full (full), .empty (empty),
      .wr_pt (wr_pt), .rd_pt (rd_pt),
      .wr_en (wr_en), .rd_en (rd_en),
      .din (din), .dout (dout),
      .count (count)
      );
  
endmodule
`endif // TOP_SV