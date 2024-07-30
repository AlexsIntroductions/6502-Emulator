#pragma once
#include <iostream>
#include <fstream>
#include <cstdint>
#include <string>

class nes_mem
{
    uint8_t mem[0xFFFF];
public:
    nes_mem();
    ~nes_mem();

    // Component Functions
    void load(std::string filename);
    void load2address(std::string filename, uint16_t address);
    void loadNesTest();

    // General Memory Access Functions
    uint8_t read_8(uint16_t addr);
    uint16_t read_16(uint16_t addr);
    void write_8(uint16_t addr, uint8_t val);
    void write_16(uint16_t addr, uint16_t val);

    // Stack Access Functions
    uint8_t peek(uint8_t sp, uint8_t n);
    uint8_t pop(uint8_t sp);
    void push(uint8_t sp, uint8_t val);

    // ZPG Access Functions
    uint8_t readZPG_8(uint8_t addr);
    uint16_t readZPG_16(uint8_t addr);

    uint16_t read_16_wrap(uint16_t addr);

    //Debug Functions
    void print_mem();
    void print_zpg();
    void print_stack();
    
private:
    void bytes2hex(unsigned char *src, char *out, int len);
    void bytes2hex(char *src, char *out, int len);
};