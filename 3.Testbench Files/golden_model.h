#ifndef GOLDEN_MODEL_H
#define GOLDEN_MODEL_H

#include <queue>

#include "fifo_item.h"
#include "golden_item.h"
#include "functional_coverage.h"
#include "scoreboard.h"

class FunctionalCoverage;
class Scoreboard;

class GoldenModel {
    private :
        FunctionalCoverage* fcov;
        Scoreboard* scb;

        struct coverage_item {
            unsigned char reset;
            unsigned char write, read;
            unsigned char full, empty;
            int fill_level;
            int depth;
        };

        std::queue<uint32_t> golden_fifo;

        uint32_t golden_data;

        coverage_item cov_col;

        int DEPTH = 8;

    public :
        GoldenModel (FunctionalCoverage* _fcov, Scoreboard* _scb);

        void get_golden_input (const InputItem& tr);
};
#endif // GOLDEN_MODEL_H