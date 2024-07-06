#pragma once
#include <iostream>
#include <fstream>
#include <cstdint>
#include <string>

class nes_mem
{
    uint8_t mem[0xFFFF];
    int debug = 0;
public:
    nes_mem();
    ~nes_mem();

    // Component Functions
    void load(std::string filename);

    // General Memory Access Functions
    uint8_t read_8(uint16_t addr);
    uint16_t read_16(uint16_t addr);
    void write_8(uint16_t addr, uint8_t val);
    void write_16(uint16_t addr, uint16_t val);

    // Stack Access Functions
    uint8_t peek(uint8_t sp, uint8_t n);
    uint8_t pop(uint8_t sp);
    void push(uint8_t sp, uint8_t val);


    //Debug Functions
    void set_debug(int val);
    void print_mem();

    //Temp Functions

private:
    void bytes2hex(unsigned char *src, char *out, int len);
};