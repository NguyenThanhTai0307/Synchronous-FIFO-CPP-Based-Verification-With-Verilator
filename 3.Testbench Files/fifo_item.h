#ifndef INPUT_ITEM_H
#define INPUT_ITEM_H

#include <cstdint>

struct InputItem
{
    unsigned char wr_en;
    unsigned char rd_en;
    unsigned char rstn;
    uint32_t din ;
};

struct OutputItem
{
    unsigned char rd_en;
    unsigned char rstn;
    unsigned char full;
    unsigned char empty;
    uint32_t dout;
};

#endif // INPUT_ITEM_H