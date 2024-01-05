#include "../inc/nes_mem.h"

using namespace std;

char HexLookUp2[] = "0123456789abcdef";

nes_mem::nes_mem(){
    cout << "In MEM" << endl;
    //TEST PROGRAM
    //LDA #$01
    //STA $0200
    //LDA #$05
    //STA $0201
    //LDA #$08
    //STA $0202
    mem[0] = 0x01; 
    mem[1] = 0x8d; 
    mem[2] = 0x00; 
    mem[3] = 0x02; 
    mem[4] = 0xa9; 
    mem[5] = 0x05; 
    mem[6] = 0x8d; 
    mem[7] = 0x01; 
    mem[8] = 0x02; 
    mem[9] = 0xa9; 
    mem[10] = 0x08; 
    mem[11] = 0x8d; 
    mem[12] = 0x02; 
    mem[13] = 0x02;
    cout << "MEM DONE READING" << endl;
}

nes_mem::~nes_mem(){
    
}

unsigned char nes_mem::read(unsigned char addr){
    return mem[addr];
}

void nes_mem::write(unsigned char addr, unsigned char val){
    mem[addr] = val;
}

void nes_mem::bytes2hex(unsigned char *src, char* out, int len){
    while(len--)
    {
        *out++ = HexLookUp2[*src >> 4];
        *out++ = HexLookUp2[*src & 0x0F];
        src++;
    }
    *out = 0;
}

void nes_mem::print_mem(){
    char buffer[2048*2 + 1];  
    bytes2hex(mem, buffer, sizeof(mem));
    for(int i = 0; i < sizeof(buffer) / sizeof(int); i+=2){
        if(i % 16 == 0){
            cout << endl;
        }
        else if (i % 8 == 0){
            cout << " ";
        }
        cout << buffer[i] << buffer[i+1] << " ";
        
    }
}

