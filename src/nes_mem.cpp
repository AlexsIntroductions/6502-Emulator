#include "../inc/nes_mem.h"

using namespace std;

nes_mem::nes_mem()
{
    if (debug == 1){
        cout << "New NES_MEM Created" << endl;
    }
    // TEST PROGRAM
    // LDA #$01
    // STA $0200
    // LDA #$05
    // STA $0201
    // LDA #$08
    // STA $0202
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
}

nes_mem::~nes_mem()
{
    delete[] mem;
}

unsigned char nes_mem::read_8(unsigned char addr)
{
    if (debug == 1){
        cout << "Memory 8 read: " << mem[addr] << endl;
    }
    return mem[addr];
}

// LITTLE ENDIAN
unsigned short nes_mem::read_16(unsigned char addr)
{
    if (debug == 1){
        cout << "Memory 16 read: " << ((mem[addr + 1] << 8) | mem[addr]) << endl;
    }
    return (unsigned short)((mem[addr + 1] << 8) | mem[addr]);
}

void nes_mem::write_8(unsigned char addr, unsigned char val)
{
    if (debug == 1){
        cout << "Memory 8 write: " << val << " | To: " << addr << endl;
    }
    mem[addr] = val;
}

// LITTLE ENDIAN
void nes_mem::write_16(unsigned char addr, unsigned short val)
{
    if (debug == 1){
        cout << "Memory 16 write: " << (val >> 8) << " | To: " << addr << endl;
        cout << "               : " << (unsigned char)val << " | To: " << addr + 1 << endl;
    }
    mem[addr + 1] = (unsigned char)val;
    mem[addr] = (unsigned char)(val >> 8);
}

void nes_mem::load(string filename)
{

    // ROM reading code taken from: https://forums.nesdev.org/viewtopic.php?t=15104

    ifstream rom;
    int romSize;
    rom.open(filename, ios_base::in | ios::binary);
    if (!rom.is_open())
    {
        cout << "Error Loading ROM: " << filename << endl;
        return;
    }

    if (debug == 1){
        cout << "READING ROM" << endl;
    }

    rom.seekg(0, rom.end);
    romSize = rom.tellg();
    rom.seekg(0, rom.beg);

    if (debug == 1){
        cout << "ROM SIZE: " << romSize << endl;
    }

    char *buffer = new char[romSize];
    rom.read(reinterpret_cast<char *>(buffer), romSize);

    if (debug == 1){
        cout << "ROM BUFFER LOADED" << endl;
    }

    //Erase Current Memory ??(Find cleaner way to do this)
    for (unsigned int i = 0; i < 0xFFFF; i++)
    {
        mem[i] = 0;
    }

    if (debug == 1){
        cout << "DONE WRITING MEMORY" << endl;
    }

    //Load ROM from 0x4020 to 0xFFFF
    for (unsigned int i = 0x4020; i < 0xFFFF; i++)
    {
        mem[i] = (unsigned char)buffer[i];
    }

    if (debug == 1){
        cout << "ROM Loaded, Current Memory State: " << endl;
        char output[0xFFFF * 2];
        bytes2hex(this->mem, output, romSize);
        for (int i = 0; i < sizeof(output); i += 2)
        {
            if (i % 120 == 0)
            {
                cout << endl;
            }
            else if (i % 8 == 0)
            {
                cout << " ";
            }
            cout << output[i] << output[i + 1] << " ";
        }
        cout << endl;
    }
}

void nes_mem::set_debug(int val){
    debug = val;
}

void nes_mem::bytes2hex(unsigned char *src, char *out, int len)
{
    char HexLookUp[] = "0123456789abcdef";
    while (len--)
    {
        *out++ = HexLookUp[*src >> 4];
        *out++ = HexLookUp[*src & 0x0F];
        src++;
    }
    *out = 0;
}

void nes_mem::print_mem()
{
    char buffer[0xFFFF * 2 + 1];
    bytes2hex(mem, buffer, sizeof(mem));
    for (int i = 0; i < sizeof(buffer) / sizeof(int); i += 2)
    {
        if (i % 16 == 0)
        {
            cout << endl;
        }
        else if (i % 8 == 0)
        {
            cout << " ";
        }
        cout << buffer[i] << buffer[i + 1] << " ";
    }
}
