#include "../inc/nes.h"

using namespace std;

nes::nes(){
    cout << "In NES" << endl;
    cpu = new nes_cpu();
    ppu = new nes_ppu();
    apu = new nes_apu();
    mem = nullptr;

    window = nullptr;
}

nes::nes(sf::RenderWindow* _window){
    cout << "In NES" << endl;
    cpu = new nes_cpu();
    ppu = new nes_ppu();
    apu = new nes_apu();
    mem = nullptr;

    window = _window;
}

nes::~nes(){
    
}

void nes::load(nes_mem* _mem){
    mem = _mem;
}

void nes::eject(){
}

void nes::start(){
    //If there isnt a memory loaded
    if(mem == nullptr){
        cout << "Not Started" << endl;
        return;
    }
    cout << "Started" << endl;


    if(debug == 1){
        mem->print_mem();
    }
}

void nes::reset(){

}