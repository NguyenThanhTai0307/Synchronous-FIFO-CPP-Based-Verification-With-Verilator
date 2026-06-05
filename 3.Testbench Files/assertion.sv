`ifndef ASSERTION_SV
`define ASSERTION_SV
module Assertion #(parameter WIDTH = 8,
parameter DEPTH = 8) (
  input logic clk, rstn,
  input logic rd_en, wr_en,
  input logic full, empty,
  input logic [WIDTH - 1 : 0] din, dout,
  input logic [$clog2(DEPTH) - 1 : 0] wr_pt = 0,
  input logic [$clog2(DEPTH) - 1 : 0] rd_pt = 0,
  input logic [$clog2(DEPTH) : 0] count = 0
);

  // Checks states
  property full_state;
    @(posedge clk) disable iff(!rstn)
    (count == DEPTH) |-> (full == 1);
  endproperty

  property empty_state;
    @(posedge clk) disable iff(!rstn)
    (count == 0) |-> (empty == 1);
  endproperty

  // Checks stability of dout
  property stable_dout;
    @(posedge clk) disable iff(!rstn)
    $past(!rd_en && !empty) |-> ($stable(dout));
  endproperty

  // Checks pointers
  property write_pointer_full;
    @(posedge clk) disable iff(!rstn)
    (wr_en && full && !rd_en) |=> $stable(wr_pt);
  endproperty

  property read_pointer_empty;
    @(posedge clk) disable iff(!rstn)
    (rd_en && empty && !wr_en) |=> $stable(rd_pt);
  endproperty

  //==============================================
  //               PROPERTY ASSERT
  //==============================================
  a_full_state : assert property(full_state);

  a_empty_state : assert property(empty_state);

  a_stable_dout : assert property(stable_dout);

  a_write_pointer_full : assert property(write_pointer_full);

  a_read_pointer_empty : assert property(read_pointer_empty);
  
  //==============================================
  //                PROPERTY COVER
  //==============================================
/*  c_full_state : cover property(full_state)
    $display("full_state is covered!");

  c_empty_state : cover property(empty_state)
    $display("empty_state is covered!");

  c_stable_dout : cover property(stable_dout)
    $display("stable_dout is covered!");

  c_write_pointer_full : cover property(write_pointer_full)
    $display("write_pointer_full is covered!");

  c_read_pointer_empty : cover property(read_pointer_empty)
    $display("read_pointer_empty is covered!");
*/
endmodule
`endif // ASSERTION_SV