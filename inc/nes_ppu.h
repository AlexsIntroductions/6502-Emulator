#pragma once
#include <iostream>
#include <cstdint>
#include "../inc/nes_mem.h"

class nes_ppu{
    nes_mem *mem;
    int debug = 0;
public:
    nes_ppu();
    ~nes_ppu();
    void set_mem(nes_mem* _mem);

    //Debug Functions
    void set_debug(int val);
private:


    
};