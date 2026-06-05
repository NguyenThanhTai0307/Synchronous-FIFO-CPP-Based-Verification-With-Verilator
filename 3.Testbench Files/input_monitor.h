#ifndef INPUT_MONITOR_H
#define INPUT_MONITOR_H

#include "Vtop.h"
#include "fifo_item.h"
#include "golden_model.h"

class GoldenModel;

class InputMonitor {
    private :
        Vtop* dut;
        GoldenModel* gm;

    public :
        InputMonitor (Vtop* _dut, GoldenModel* _gm);

        void input_sample();
};

#endif // INPUT_MONITOR_H