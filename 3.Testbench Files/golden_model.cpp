#include "golden_model.h"

GoldenModel::GoldenModel (FunctionalCoverage* _fcov, Scoreboard* _scb) :
    fcov (_fcov),
    scb (_scb) {}

void GoldenModel::get_golden_input (const InputItem& tr) {     
    bool valid_write = tr.wr_en && (golden_fifo.size() < DEPTH);
    bool valid_read = tr.rd_en && (golden_fifo.size() > 0);
    golden_item item;

    // Collect Coverage Data
    cov_col.reset = tr.rstn;
    cov_col.read = tr.rd_en;
    cov_col.write = tr.wr_en;
    cov_col.full = (golden_fifo.size() == DEPTH);
    cov_col.empty = (golden_fifo.size() == 0);
    cov_col.fill_level = golden_fifo.size();
    cov_col.depth = DEPTH;

    fcov->sample_coverage(
        cov_col.reset,
        cov_col.write,
        cov_col.read,
        cov_col.full,
        cov_col.empty,
        cov_col.fill_level,
        cov_col.depth
    );

    if (!tr.rstn) {
        while (!golden_fifo.empty()) golden_fifo.pop();

        std::cout << "[GOLDEN MODEL] RESET ASSERT --> FIFO CLEARED" << std::endl;
    }
    else {
        if (valid_read) {
            golden_data = golden_fifo.front();
            golden_fifo.pop();
        }
        else if (tr.rd_en) {
            std::cout << "[GOLDEN MODEL] Pop Expected : EMPTY" << std::endl;
        }

        if (valid_write) {
            golden_fifo.push(tr.din);
        
            std::cout << "[GOLDEN MODEL] Push Expected At 0x" << golden_fifo.size() 
            << " --> DIN : 0x" << std::hex << tr.din << std::endl;
        }
        else if (tr.wr_en) {
            std::cout << "[GOLDEN MODEL] Push Expected : FULL" << std::endl;
        }
        
        if (valid_read) {
            item.exp_data = golden_data;
            item.exp_full = (golden_fifo.size() == DEPTH);
            item.exp_empty = (golden_fifo.size() == 0);

            std::cout << "[GOLDEN MODEL] Pop Expected --> DOUT : 0x" << std::hex << 
            item.exp_data << " || FULL : " << +item.exp_full << " || EMPTY : " <<
            +item.exp_empty << std::endl;
        
            scb->write_exp(item);
        }
    }
}

