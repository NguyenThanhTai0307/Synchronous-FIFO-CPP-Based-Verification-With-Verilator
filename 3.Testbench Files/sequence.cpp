#include "sequence.h"

Sequence::Sequence (Driver* _drv, int master_seed) :
    drv (_drv),
    rng (master_seed),
    data_range (0, 0xFF),
    write_range (0, 1),
    read_range (0, 1),
    reset_range (0, 1) {}

void Sequence::item_gen (unsigned char rstn, unsigned char wr_en, unsigned char rd_en, uint32_t din) {
    InputItem item;

    item.rstn = rstn;
    item.wr_en = wr_en;
    item.rd_en = rd_en;
    item.din = din;

    drv->item_push(item);
}

void Sequence::fill_drain_test () {
    // Write until full
    for (int i = 0; i < DEPTH; i++) {
        item_gen (1, 1, 0, data_range(rng));
    }

    //Read until empty
    for (int i = 0; i < DEPTH; i++) {
        item_gen (1, 0, 1, 0x00);
    }
}

void Sequence::concurrent_rw_test () {
    // Concurrent access at empty
    item_gen (1, 1, 1, 0xAA);

    // Fill to mid-range
    for (int i = 0; i < DEPTH/2; i++) {
        item_gen (1, 1, 0, data_range(rng));
    }
    
    // Concurrent access at mid-range
    for (int i = 0; i < 3; i++) {
        item_gen (1, 1, 1, 0xBB);
    }

    // Fill to full
    for (int i = 0; i < DEPTH/2; i++) {
        item_gen (1, 1, 0, data_range(rng));
    }

    // Concurrent access at full
    item_gen (1, 1, 1, 0xCC);

    // Drain to finish safely
    for (int i = 0; i < DEPTH; i++) {
        item_gen (1, 0, 1, 0x00);
    }
}

void Sequence::random_test (int trans_num) {
    for (int i = 0; i < trans_num; i++) {
        item_gen (1, write_range(rng), read_range(rng), data_range(rng));
    }
}

void Sequence::reset_stress_test () {
    // Fill to full
    for (int i = 0; i < DEPTH; i++) {
        item_gen (1, 1, 0, data_range(rng));
    }

    // Hard reset at full
    item_gen (0, 1, 0, 0x00);

    // Write a few items (mid-range)
    for (int i = 0; i < 4; i++) {
        item_gen (1, 1, 0, 0xFF);
    }

    // Hard reset during active read
    item_gen (0, 0, 1, 0x00);

    // Write a few items (mid-range)
    for (int i = 0; i < 4; i++) {
        item_gen (1, 1, 0, 0xFF);
    }

    // Read until empty
    for (int i = 0; i < 4; i++) {
        item_gen (1, 0, 1, 0x00);
    }

    // Hard reset at empty
    item_gen (0, 1, 0, 0x00);
}

void Sequence::overflow_underflow_test () {
    // Write when already full
    for (int i = 0; i < DEPTH + 1; i++) {
        item_gen (1, 1, 0, data_range(rng));
    }

    // Read when already empty
    for (int i = 0; i < DEPTH + 1; i++) {
        item_gen (1, 0, 1, 0x00);
    }
}
