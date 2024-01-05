#pragma once
#include <iostream>
#include <cstdint>

class nes_mem
{
    unsigned char mem[250000];

public:
    nes_mem();
    ~nes_mem();
    unsigned char read(unsigned char addr);
    void write(unsigned char addr, unsigned char val);
    void print_mem();

private:
    void bytes2hex(unsigned char *src, char *out, int len);
};