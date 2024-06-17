#pragma once
#include <iostream>
#include <cstdint>
#include <string>
//#include <SFML/Graphics.hpp>
#include "../inc/nes_cpu.h"
#include "../inc/nes_ppu.h"
#include "../inc/nes_apu.h"
#include "../inc/nes_mem.h"

class nes{
    nes_cpu* cpu;
    nes_ppu* ppu;
    nes_apu* apu;
    nes_mem* mem;

    int debug = 0;

    //sf::RenderWindow* window;
public:
    nes();
    //nes(sf::RenderWindow* _window);
    ~nes();
    void load(std::string filename);
    void eject();
    void start();
    void reset();

    //Debug Functions
    void set_debug(int val);

private:

};