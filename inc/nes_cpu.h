#pragma once
#include <iostream>
#include <cstdint>
#include <string>
#include "../inc/nes_mem.h"
/*
RAM                     :   [0x0000 … 0x2000] 
  -Zero Page        :   [0x0000 … 0x00FF]
  -STACK            :   [0x0100 … 0x01FF]
NES MODULES             :   [0x2000 … 0x4020]
CARTRIDGE RAM           :   [0x6000 … 0x8000]
PROGRAM ROM             :   [0x8000 … 0xFFFF]
  -NMI handler      :   [0xFFFA … 0xFFFB]
  -Power On Reset   :   [0xFFFC … 0xFFFD]
  -BRK/IntReqHandler:   [0xFFFE … 0xFFFF]

*/

class nes_cpu{

    //----------General Registers----------//
    //Accumulator
    unsigned char a;
    //X register
    unsigned char x;
    //Y register
    unsigned char y;
    //----------Status Register----------//
    // 7 - N: negative result
    // 6 - V: overflow
    // 5 - 
    // 4 - B: break
    // 3 - D: decimal mode
    // 2 - I: interrupt disable
    // 1 - Z: zero result
    // 0 - C: carry
    unsigned char status;
    //----------Stack Pointer----------//
    unsigned char sp;
    //----------Address Bus?----------//
    unsigned short pc;

    int cycles = 0;

    nes_mem *mem;

    int debug = 0;
    
public:
    nes_cpu();
    ~nes_cpu();
    void evaluate(unsigned char opcocde);
    void set_mem(nes_mem* _mem);
    void print_CPU_state();

    //Debug Functions
    void set_debug(int val);

private:

    //Addressing Mode Functions
      //return the byte of data that is to be acted on

    //Implicit
    void* IMP();
    //Accumulator
    void* ACC();
    //Immediate
    void* IMM();
    //Zero Page
    void* ZPG();
    //Zero Page X
    void* ZPX();
    //Zero Page Y
    void* ZPY();
    //Relative
    void* REL();
    //Absolute
    void* ABS();
    //Absolute X
    void* ABX();
    //Absolute Y
    void* ABY();
    //Indirect
    void* IND();
    //Indexed Indirect
    void* IID();
    //Indirect Indexed
    void* IDI();

    void bytes2hex (unsigned char *src, char *out, int len);
};