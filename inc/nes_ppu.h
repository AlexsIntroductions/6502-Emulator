#pragma once
#include <iostream>
#include <cstdint>
#include "../inc/nes_mem.h"

class nes_ppu{
    nes_mem *mem;
public:
    nes_ppu();
    ~nes_ppu();
    void set_mem(nes_mem* _mem);
private:
    
};