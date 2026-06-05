#include "input_monitor.h"

InputMonitor::InputMonitor (Vtop* _dut, GoldenModel* _gm) :
    dut (_dut),
    gm (_gm) {}

void InputMonitor::input_sample () {
    InputItem item;

    item.rstn = dut->rstn;
    item.wr_en = dut->wr_en;
    item.rd_en = dut->rd_en;
    item.din = dut->din;

    gm->get_golden_input(item);
}