#include "../inc/nes_mem.h"

using namespace std;

nes_mem::nes_mem()
{
    if (debug == 1)
    {
        cout << "New NES_MEM Created" << endl;
    }

    // Erase Current Memory ??(Find cleaner way to do this)
    for (unsigned int i = 0; i < 0xFFFF; i++)
    {
        mem[i] = 0;
    }

    if (debug == 1)
    {
        cout << "DONE CLEARING MEMORY" << endl;
    }
}

nes_mem::~nes_mem()
{
    delete[] mem;
}

//--------------------Component Functions--------------------//

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

    if (debug == 1)
    {
        cout << "READING ROM" << endl;
    }

    rom.seekg(0, rom.end);
    romSize = rom.tellg();
    rom.seekg(0, rom.beg);

    if (debug == 1)
    {
        cout << "ROM SIZE: " << romSize << endl;
    }

    char *buffer = new char[romSize];
    rom.read(reinterpret_cast<char *>(buffer), romSize);

    if (debug == 1)
    {
        cout << "ROM BUFFER LOADED" << endl;
    }

    // Erase Current Memory ??(Find cleaner way to do this)
    for (unsigned int i = 0; i < 0xFFFF; i++)
    {
        mem[i] = 0;
    }

    if (debug == 1)
    {
        cout << "DONE WRITING MEMORY" << endl;
    }

    // Load ROM from 0x4020 to 0xFFFF
    for (unsigned int i = 0x4020; i < 0xFFFF; i++)
    {
        mem[i] = (unsigned char)buffer[i];
    }

    if (debug == 1)
    {
        cout << "ROM Loaded, Current Memory State: " << endl;
        char output[0xFFFF * 2];
        bytes2hex(this->mem, output, romSize);
        print_mem();
    }
}

void nes_mem::load2address(string filename, uint16_t address)
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

    if (debug == 1)
    {
        cout << "READING ROM" << endl;
    }

    rom.seekg(0, rom.end);
    romSize = rom.tellg();
    rom.seekg(0, rom.beg);

    if (debug == 1)
    {
        cout << "ROM SIZE: " << romSize << endl;
    }

    char *buffer = new char[romSize];
    rom.read(reinterpret_cast<char *>(buffer), romSize);

    if (debug == 1)
    {
        cout << "ROM BUFFER LOADED" << endl;
    }

    // Erase Current Memory ??(Find cleaner way to do this)
    for (unsigned int i = 0; i < 0xFFFF; i++)
    {
        mem[i] = 0;
    }

    if (debug == 1)
    {
        cout << "DONE WRITING MEMORY" << endl;
    }

    // Load ROM from 0x4020 to 0xFFFF
    for (unsigned int i = address; i < 0xFFFF; i++)
    {
        mem[i] = (unsigned char)buffer[i];
    }

    if (debug == 1)
    {
        cout << "ROM Loaded, Current Memory State: " << endl;
        char output[0xFFFF * 2];
        bytes2hex(this->mem, output, romSize);
        print_mem();
    }
}

void nes_mem::loadNesTest()
{
    // ROM reading code taken from: https://forums.nesdev.org/viewtopic.php?t=15104

    ifstream rom;
    int romSize;
    rom.open("nestest.nes", ios_base::in | ios::binary);
    if (!rom.is_open())
    {
        cout << "Error Loading NESTEST" << endl;
        return;
    }

    if (debug == 1)
    {
        cout << "READING ROM" << endl;
    }

    rom.seekg(0, rom.end);
    romSize = rom.tellg();
    rom.seekg(0, rom.beg);

    if (debug == 1)
    {
        cout << "ROM SIZE: " << std::hex << romSize << endl;
    }

    char *buffer = new char[romSize];
    rom.read(reinterpret_cast<char *>(buffer), romSize);

    if (debug == 1)
    {
        cout << "ROM BUFFER CREATED" << endl;
        // char buffer2[0xFFFF * 2 + 1];
        // bytes2hex(buffer, buffer2, romSize);
        // for (int i = 0; i < romSize; i += 2)
        // {
        //     // Every 0x100 bytes print a line
        //     if (i % 0xC0 == 0)
        //     {
        //         cout << endl;
        //         cout << std::hex << i << " : ";
        //     }
        //     else if (i % 8 == 0)
        //     {
        //         cout << " ";
        //     }
        //     cout << buffer2[i] << buffer2[i + 1] << " ";
        // }
        // cout << endl;
    }

    for (uint16_t i = 0; i < 0x4000; i+=1)
    {
        uint8_t temp = (uint8_t)buffer[i + 0x10];
        mem[(uint16_t)(0x8000 + i)] = temp;
        mem[(uint16_t)(0xC000 + i)] = temp;
    }

    if (debug == 1)
    {
        cout << endl;
        cout << "ROM Loaded, Current Memory State: " << endl << endl;
        char output[0xFFFF * 2];
        bytes2hex(this->mem, output, romSize);
        print_mem();
    }
}

//--------------------General Memory Access Functions--------------------//

uint8_t nes_mem::read_8(uint16_t addr)
{
    if (debug == 1)
    {
        cout << "Memory 8 read: " << mem[addr] << endl;
    }
    return mem[addr];
}

// LITTLE ENDIAN
uint16_t nes_mem::read_16(uint16_t addr)
{
    if (debug == 1)
    {
        cout << "Memory 16 read: " << ((mem[addr + 1] << 8) | mem[addr]) << endl;
    }
    return (uint16_t)((mem[addr + 1] << 8) | mem[addr]);
}

void nes_mem::write_8(uint16_t addr, uint8_t val)
{
    if (debug == 1)
    {
        cout << "Memory 8 write: " << val << " | To: " << addr << endl;
    }
    mem[addr] = val;
}

// LITTLE ENDIAN
void nes_mem::write_16(uint16_t addr, uint16_t val)
{
    if (debug == 1)
    {
        cout << "Memory 16 write: " << (val >> 8) << " | To: " << addr << endl;
        cout << "               : " << (uint8_t)val << " | To: " << addr + 1 << endl;
    }
    mem[addr + 1] = (uint8_t)val;
    mem[addr] = (uint8_t)(val >> 8);
}

//--------------------Stack Access Functions--------------------//

uint8_t nes_mem::peek(uint8_t sp, uint8_t n)
{
    return mem[(0x0100 & sp) - n - 1];
}

uint8_t nes_mem::pop(uint8_t sp)
{
    return mem[0x0100 & sp];
}

void nes_mem::push(uint8_t sp, uint8_t val)
{
    mem[0x0100 & sp] = val;
}

//--------------------Debug Functions--------------------//

void nes_mem::set_debug(int val)
{
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

void nes_mem::bytes2hex(char *src, char *out, int len)
{
    char HexLookUp[] = "0123456789abcdef";
    while (len--)
    {
        *out++ = HexLookUp[(unsigned char)*src >> 4];
        *out++ = HexLookUp[(unsigned char)*src & 0x0F];
        src++;
    }
    *out = 0;
}

void nes_mem::print_mem()
{
    char tempBuffer[0x1FFFF];
    bytes2hex(mem, tempBuffer, 0xFFFF + 1);
    for (int i = 0; i <= sizeof(tempBuffer) / sizeof(char); i += 2)
    {
        // Every 0x100 bytes print a line
        //if (i % 0x100 == 0)
        if ((i / 2) % 0x3C == 0)
        {
            cout << endl;
            cout << std::hex << (i / 2) << " : ";
        }
        else if (i % 8 == 0)
        {
            cout << " ";
        }
        cout << tempBuffer[i] << tempBuffer[i + 1] << " ";
    }
    cout << endl;
}