#ifndef SCOREBOARD_H
#define SCOREBOARD_H

#include <queue>

#include "golden_item.h"
#include "golden_model.h"
#include "fifo_item.h"

class GoldenModel;

class Scoreboard {
    private :
        GoldenModel* gm;

        std::queue<OutputItem> scb_queue;
        std::queue<golden_item> exp_queue;

        int match = 0;
        int mismatch = 0;

    public :
        void write_exp(const golden_item& tr);

        void write_act(const OutputItem& tr);

        void print_summary();
};
#endif // SCOREBOARD_H