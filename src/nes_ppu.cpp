#include "../inc/nes_ppu.h"

using namespace std;

nes_ppu::nes_ppu(){
    mem = nullptr;
    cout << "In PPU" << endl;
}

nes_ppu::~nes_ppu(){
    
}

void nes_ppu::set_mem(nes_mem* _mem){
    this->mem = _mem;
}

void nes_ppu::set_debug(int val){
    debug = val;
}