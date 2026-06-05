#ifndef DRIVER_H
#define DRIVER_H

#include <queue>

#include "Vtop.h"
#include "fifo_item.h"

class Driver {
    private : 
        Vtop* dut;

        std::queue<InputItem> input_queue;

    public :
        Driver (Vtop* _dut);

        void item_push (const InputItem& tr);

        void reset ();

        void drive ();

        bool is_finished();
};
#endif // DRIVER_H