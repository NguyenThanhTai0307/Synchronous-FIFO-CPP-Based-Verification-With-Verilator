#include "functional_coverage.h"

void FunctionalCoverage::sample_coverage(
    unsigned char rstn, 
    unsigned char wr_en, 
    unsigned char rd_en, 
    unsigned char full, 
    unsigned char empty, 
    int fill_level,
    int depth
) {
    // Basic Signal Coverpoints
    if (rstn == 0) cp_rstn_rst++; else cp_rstn_no_rst++;
    if (rd_en == 1) cp_rd_en_rd++; else cp_rd_en_no_rd++;
    if (wr_en == 1) cp_wr_en_wr++; else cp_wr_en_no_wr++;
    if (full == 1) cp_full_fll++; else cp_full_no_fll++;
    if (empty == 1) cp_empty_empt++; else cp_empty_no_empt++;

    // Fill Level Coverpoints
    if (fill_level == 0) cp_fill_empty++;
    else if (fill_level == 1) cp_fill_near_empty++;
    else if (fill_level == depth - 1) cp_fill_near_full++;
    else if (fill_level == depth) cp_fill_full++;
    else cp_fill_mid++; // [2 : DEPTH - 2]

    // Cross Coverage: Overflow/Underflow Attempts
    if (wr_en == 1 && full == 1) cross_write_when_full++;
    if (rd_en == 1 && empty == 1) cross_read_when_empty++;

    // Cross Coverage: Simultaneous Read-Write
    if (rd_en == 1 && wr_en == 1) {
        if (fill_level == depth) cross_rd_wr_at_full++;
        else if (fill_level == 0) cross_rd_wr_at_empty++;
        else cross_rd_wr_at_mid_range++;
    }

    // Cross Coverage: Reset Timing
    if (rstn == 0) {
        if (full == 1) cross_reset_at_full++;
        if (empty == 1) cross_reset_at_empty++;
    }
}

void FunctionalCoverage::report_coverage() {
    std::cout << "\n===================================================\n";
    std::cout << "            FIFO FUNCTIONAL COVERAGE REPORT          \n";
    std::cout << "===================================================\n";
    
    std::cout << "[Control Signals]\n";
    std::cout << "  RSTN      : rst = " << cp_rstn_rst << " | no_rst = " << cp_rstn_no_rst << "\n";
    std::cout << "  RD_EN     : rd = " << cp_rd_en_rd << " | no_rd = " << cp_rd_en_no_rd << "\n";
    std::cout << "  WR_EN     : wr = " << cp_wr_en_wr << " | no_wr = " << cp_wr_en_no_wr << "\n";
    std::cout << "  FULL      : fll = " << cp_full_fll << " | no_fll = " << cp_full_no_fll << "\n";
    std::cout << "  EMPTY     : empt = " << cp_empty_empt << " | no_empt = " << cp_empty_no_empt << "\n";
    
    std::cout << "\n[Fill Levels]\n";
    std::cout << "  Empty      : " << cp_fill_empty << "\n";
    std::cout << "  Near Empty : " << cp_fill_near_empty << "\n";
    std::cout << "  Mid Range  : " << cp_fill_mid << "\n";
    std::cout << "  Near Full  : " << cp_fill_near_full << "\n";
    std::cout << "  Full       : " << cp_fill_full << "\n";

    std::cout << "\n[Critical Corner Cases]\n";
    std::cout << "  Write when Full (Overflow) : " << cross_write_when_full << "\n";
    std::cout << "  Read when Empty (Underflow): " << cross_read_when_empty << "\n";
    std::cout << "  Simultaneous RW (Empty)    : " << cross_rd_wr_at_empty << "\n";
    std::cout << "  Simultaneous RW (Mid)      : " << cross_rd_wr_at_mid_range << "\n";
    std::cout << "  Simultaneous RW (Full)     : " << cross_rd_wr_at_full << "\n";
    std::cout << "  Reset at Full Capacity     : " << cross_reset_at_full << "\n";
    std::cout << "  Reset at Empty Capacity    : " << cross_reset_at_empty << "\n";
    std::cout << "===================================================\n\n";
}