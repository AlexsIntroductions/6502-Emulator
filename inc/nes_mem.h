#pragma once
#include <iostream>
#include <fstream>
#include <cstdint>
#include <string>

class nes_mem
{
    unsigned char mem[0xFFFF];
    int debug = 0;
public:
    nes_mem();
    ~nes_mem();
    unsigned char read_8(unsigned char addr);
    unsigned short read_16(unsigned char addr);
    void write_8(unsigned char addr, unsigned char val);
    void write_16(unsigned char addr, unsigned short val);
    void load(std::string filename);

    //Debug Functions
    void set_debug(int val);
    void print_mem();

    //Temp Functions

private:
    void bytes2hex(unsigned char *src, char *out, int len);
};