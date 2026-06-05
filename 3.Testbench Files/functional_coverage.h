#ifndef FUNCTIONAL_COVERAGE_H
#define FUNCTIONAL_COVERAGE_H

#include <iostream>
#include <iomanip>

class FunctionalCoverage {
    private :
        // ============================================================================
        // 1. Coverpoint Counters
        // ============================================================================
        int cp_rstn_rst = 0, cp_rstn_no_rst = 0;
        int cp_rd_en_rd = 0, cp_rd_en_no_rd = 0;
        int cp_wr_en_wr = 0, cp_wr_en_no_wr = 0;
        int cp_full_fll = 0, cp_full_no_fll = 0;
        int cp_empty_empt = 0, cp_empty_no_empt = 0;

        // Fill Level Counters
        int cp_fill_empty = 0;
        int cp_fill_near_empty = 0;
        int cp_fill_mid = 0;
        int cp_fill_near_full = 0;
        int cp_fill_full = 0;

        // ============================================================================
        // 2. Cross Coverage (Corner Cases) Counters
        // ============================================================================
        int cross_write_when_full = 0;
        int cross_read_when_empty = 0;

        int cross_rd_wr_at_full = 0;
        int cross_rd_wr_at_empty = 0;
        int cross_rd_wr_at_mid_range = 0;

        int cross_reset_at_full = 0;
        int cross_reset_at_empty = 0;

    public :
        void sample_coverage(
            unsigned char rstn, 
            unsigned char wr_en, 
            unsigned char rd_en, 
            unsigned char full, 
            unsigned char empty, 
            int fill_level,
            int depth
        );
        
        void report_coverage();
};
#endif // FUNCTIONAL_COVERAGE_H