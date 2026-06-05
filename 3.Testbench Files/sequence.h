#ifndef SEQUENCE_H
#define SEQUENCE_H

#include <random>

#include "fifo_item.h"
#include "driver.h"

class Sequence {
    private :
        int DEPTH = 8;
        
        Driver* drv;

        std::mt19937 rng;

        std::uniform_int_distribution<uint32_t> data_range;
        std::uniform_int_distribution<unsigned char> write_range;
        std::uniform_int_distribution<unsigned char> read_range;
        std::uniform_int_distribution<unsigned char> reset_range;

        void item_gen (unsigned char rstn,
                        unsigned char wr_en,
                        unsigned char rd_en,
                        uint32_t din);
    
    public :
        Sequence (Driver* _drv, int master_seed);

        void fill_drain_test ();

        void concurrent_rw_test ();

        void random_test (int trans_num);

        void reset_stress_test ();

        void overflow_underflow_test ();
};
#endif // SEQUENCE_H