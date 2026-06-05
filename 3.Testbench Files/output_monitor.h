#ifndef OUTPUT_MONITOR_H
#define OUTPUT_MONITOR_H

#include "Vtop.h"
#include "fifo_item.h"
#include "scoreboard.h"

class Scoreboard;

class OutputMonitor {
    private :
        Vtop* dut;
        Scoreboard* scb;

    public :
        OutputMonitor (Vtop* _dut, Scoreboard* _scb);

        void output_sample ();
};
#endif // OUTPUT_MONITOR_H