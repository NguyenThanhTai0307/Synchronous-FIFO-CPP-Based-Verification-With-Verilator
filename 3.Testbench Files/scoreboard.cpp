#include "scoreboard.h"

void Scoreboard::write_exp (const golden_item& tr) {
    exp_queue.push(tr);
}

void Scoreboard::write_act (const OutputItem& tr) {
    golden_item item;

    if (tr.rstn == 0) {
        while (!exp_queue.empty()) exp_queue.pop();
        return;
    }
    else {
        if (tr.rd_en == 1) {
            if (!exp_queue.empty()) {
                item = exp_queue.front();
                exp_queue.pop();

                if (item.exp_data == tr.dout && item.exp_full == tr.full && item.exp_empty == tr.empty) {

                    std::cout << "DATA MATCH --> DOUT : 0x" << std::hex << item.exp_data <<
                    " || 0x" << std::hex << tr.dout << " FULL : " << +item.exp_full << " || "
                    << +tr.full << " EMPTY : " << +item.exp_empty << " || " << +tr.empty << std::endl;

                    match++;
                }
                else {
                    std::cout << "---> DATA MISMATCH --> DOUT : 0x" << std::hex << item.exp_data <<
                    " || 0x" << std::hex << tr.dout << " FULL : " << +item.exp_full << " || "
                    << +tr.full << " EMPTY : " << +item.exp_empty << " || " << +tr.empty << std::endl;

                    mismatch++;
                }
            }
            else {
                std::cerr << "[SCB] Actual read received from monitor, but expected queue is empty!" << std::endl;
            }
        }
    }
}

void Scoreboard::print_summary() {
    std::cout << "\n======================================================\n";
    std::cout << "                 SCOREBOARD SUMMARY                   \n";
    std::cout << "======================================================\n";
    std::cout << " Total Matches: " << std::dec << match << "\n";
    std::cout << " Total Mismatches:  " << std::dec << mismatch << "\n";
    if (mismatch == 0 && match > 0) {
        std::cout << " RESULT: PASS \n";
    } else {
        std::cout << " RESULT: FAIL \n";
    }
    std::cout << "======================================================\n";
}