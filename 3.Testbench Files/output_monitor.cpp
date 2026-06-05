#include "output_monitor.h"

OutputMonitor::OutputMonitor (Vtop* _dut, Scoreboard* _scb) :
    dut (_dut),
    scb (_scb) {}

void OutputMonitor::output_sample () {
    OutputItem item;
    if (dut->rd_en == 1) {
        
        item.rstn = dut->rstn;
        item.rd_en = dut->rd_en;
        item.dout = dut->dout;
        item.full = dut->full;
        item.empty = dut->empty;

        scb->write_act (item);
    }
}