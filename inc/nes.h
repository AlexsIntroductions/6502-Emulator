#pragma once
#include <iostream>
#include <cstdint>
#include <SFML/Graphics.hpp>
#include "../inc/nes_cpu.h"
#include "../inc/nes_ppu.h"
#include "../inc/nes_apu.h"
#include "../inc/nes_mem.h"

class nes{
    nes_cpu* cpu;
    nes_ppu* ppu;
    nes_apu* apu;
    nes_mem* mem;

    int debug = 1;

    sf::RenderWindow* window;
public:
    nes();
    nes(sf::RenderWindow* _window);
    ~nes();
    void load(nes_mem* _mem);
    void eject();
    void start();
    void reset();
};