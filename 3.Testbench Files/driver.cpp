#include "driver.h"

Driver::Driver (Vtop* _dut) :
    dut (_dut) {}

void Driver::item_push (const InputItem& tr) {
    input_queue.push(tr);
}

void Driver::reset () {
    while (!input_queue.empty()) input_queue.pop();
}

void Driver::drive () {
    if (!input_queue.empty()) {
        InputItem item;
        item = input_queue.front();
        input_queue.pop();

        dut->rstn = item.rstn;
        dut->wr_en = item.wr_en;
        dut->rd_en = item.rd_en;
        dut->din = item.din;
    }
    else {
        dut->rstn = 1;
        dut->wr_en = 0;
        dut->rd_en = 0;
        dut->din = 0x0;
    }
}

bool Driver::is_finished() {
    return input_queue.empty();
}