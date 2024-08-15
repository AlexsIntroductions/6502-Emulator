#include "../inc/nes_mem.h"

using namespace std;

nes_mem::nes_mem()
{
    #ifdef MEM_DEBUG
        cout << "New NES_MEM Created" << endl;
    #endif

    // Erase Current Memory ??(Find cleaner way to do this)
    for (unsigned int i = 0; i < 0xFFFF; i++)
    {
        mem[i] = 0;
    }

    #ifdef MEM_DEBUG
        cout << "DONE CLEARING MEMORY" << endl;
    #endif
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

    #ifdef MEM_DEBUG
        cout << "READING ROM" << endl;
    #endif

    rom.seekg(0, rom.end);
    romSize = rom.tellg();
    rom.seekg(0, rom.beg);

    #ifdef MEM_DEBUG
        cout << "ROM SIZE: " << romSize << endl;
    #endif

    char *buffer = new char[romSize];
    rom.read(reinterpret_cast<char *>(buffer), romSize);

    #ifdef MEM_DEBUG
        cout << "ROM BUFFER LOADED" << endl;
    #endif

    // Erase Current Memory ??(Find cleaner way to do this)
    for (unsigned int i = 0; i < 0xFFFF; i++)
    {
        mem[i] = 0;
    }

    #ifdef MEM_DEBUG
        cout << "DONE WRITING MEMORY" << endl;
    #endif

    // Load ROM from 0x4020 to 0xFFFF
    for (unsigned int i = 0x4020; i < 0xFFFF; i++)
    {
        mem[i] = (unsigned char)buffer[i];
    }

    #ifdef MEM_DEBUG
        cout << "ROM Loaded, Current Memory State: " << endl;
        char output[0xFFFF * 2];
        bytes2hex(this->mem, output, romSize);
        print_mem();
    #endif
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

    #ifdef MEM_DEBUG
        cout << "READING ROM" << endl;
    #endif

    rom.seekg(0, rom.end);
    romSize = rom.tellg();
    rom.seekg(0, rom.beg);

    #ifdef MEM_DEBUG
        cout << "ROM SIZE: " << romSize << endl;
    #endif

    char *buffer = new char[romSize];
    rom.read(reinterpret_cast<char *>(buffer), romSize);

    #ifdef MEM_DEBUG
        cout << "ROM BUFFER LOADED" << endl;
    #endif

    // Erase Current Memory ??(Find cleaner way to do this)
    for (unsigned int i = 0; i < 0xFFFF; i++)
    {
        mem[i] = 0;
    }

    #ifdef MEM_DEBUG
        cout << "DONE WRITING MEMORY" << endl;
    #endif

    // Load ROM from 0x4020 to 0xFFFF
    for (unsigned int i = address; i < 0xFFFF; i++)
    {
        mem[i] = (unsigned char)buffer[i];
    }

    #ifdef MEM_DEBUG
        cout << "ROM Loaded, Current Memory State: " << endl;
        char output[0xFFFF * 2];
        bytes2hex(this->mem, output, romSize);
        print_mem();
    #endif
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

    #ifdef MEM_DEBUG
        cout << "READING ROM" << endl;
    #endif

    rom.seekg(0, rom.end);
    romSize = rom.tellg();
    rom.seekg(0, rom.beg);

    #ifdef MEM_DEBUG
        cout << "ROM SIZE: " << std::hex << romSize << endl;
    #endif

    char *buffer = new char[romSize];
    rom.read(reinterpret_cast<char *>(buffer), romSize);

    #ifdef MEM_DEBUG
        cout << "ROM BUFFER CREATED" << endl;
    #endif

    for (uint16_t i = 0; i < 0x4000; i+=1)
    {
        uint8_t temp = (uint8_t)buffer[i + 0x10];
        mem[(uint16_t)(0x8000 + i)] = temp;
        mem[(uint16_t)(0xC000 + i)] = temp;
    }

    #ifdef MEM_DEBUG
        cout << endl;
        cout << "ROM Loaded, Current Memory State: " << endl << endl;
        char output[0xFFFF * 2];
        bytes2hex(this->mem, output, romSize);
        print_mem();
    #endif
}

void nes_mem::loadNesTestv2()
{
    // ROM reading code taken from: https://forums.nesdev.org/viewtopic.php?t=15104

    ifstream rom;
    int romSize;
    rom.open("nestest-v2.nes", ios_base::in | ios::binary);
    if (!rom.is_open())
    {
        cout << "Error Loading NESTESTv2" << endl;
        return;
    }

    #ifdef MEM_DEBUG
        cout << "READING ROM" << endl;
    #endif

    rom.seekg(0, rom.end);
    romSize = rom.tellg();
    rom.seekg(0, rom.beg);

    #ifdef MEM_DEBUG
        cout << "ROM SIZE: " << std::hex << romSize << endl;
    #endif

    char *buffer = new char[romSize];
    rom.read(reinterpret_cast<char *>(buffer), romSize);

    #ifdef MEM_DEBUG
        cout << "ROM BUFFER CREATED" << endl;
    #endif

    for (uint16_t i = 0; i < 0x4000; i+=1)
    {
        uint8_t temp = (uint8_t)buffer[i + 0x10];
        mem[(uint16_t)(0x8000 + i)] = temp;
        mem[(uint16_t)(0xC000 + i)] = temp;
    }

    #ifdef MEM_DEBUG
        cout << endl;
        cout << "ROM Loaded, Current Memory State: " << endl << endl;
        char output[0xFFFF * 2];
        bytes2hex(this->mem, output, romSize);
        print_mem();
    #endif
}

void nes_mem::loadOfficialTest()
{
    // ROM reading code taken from: https://forums.nesdev.org/viewtopic.php?t=15104

    ifstream rom;
    int romSize;
    rom.open("official.nes", ios_base::in | ios::binary);
    if (!rom.is_open())
    {
        cout << "Error Loading official" << endl;
        return;
    }

    #ifdef MEM_DEBUG
        cout << "READING ROM" << endl;
    #endif

    rom.seekg(0, rom.end);
    romSize = rom.tellg();
    rom.seekg(0, rom.beg);
    cout << romSize << endl;
    #ifdef MEM_DEBUG
        cout << "ROM SIZE: " << std::hex << romSize << endl;
    #endif

    char *buffer = new char[romSize];
    rom.read(reinterpret_cast<char *>(buffer), romSize);

    #ifdef MEM_DEBUG
        cout << "ROM BUFFER CREATED" << endl;
    #endif
    cout << "here" << endl;

    for (int i = 0; i < romSize; i++)
    {
        mem[(uint16_t)(i)] = (uint8_t)buffer[i];
    }
    cout << "here" << endl;
    print_mem();

    #ifdef MEM_DEBUG
        cout << endl;
        cout << "ROM Loaded, Current Memory State: " << endl << endl;
        char output[0xFFFF * 2];
        bytes2hex(this->mem, output, romSize);
        print_mem();
    #endif
}

//--------------------General Memory Access Functions--------------------//

uint8_t nes_mem::read_8(uint16_t addr)
{
    #ifdef MEM_DEBUG
        char buf[2];
        uint8_t temp = mem[addr];
        bytes2hex((unsigned char*)&temp, buf, 1);
        cout << "Memory 8 read: " << buf[0] << buf[1] << endl;
    #endif
    return mem[addr];
}

// LITTLE ENDIAN
uint16_t nes_mem::read_16(uint16_t addr)
{
    #ifdef MEM_DEBUG
        char buf[4];
        uint16_t temp = (uint16_t)((mem[addr + 1] << 8) | mem[addr]);
        bytes2hex((unsigned char*)&temp, buf, 2);
        cout << "Memory 16 read: " << buf[0] << buf[1] << buf[2] << buf[3] << endl;
    #endif
    return (uint16_t)((mem[addr + 1] << 8) | mem[addr]);
}

void nes_mem::write_8(uint16_t addr, uint8_t val)
{
    #ifdef MEM_DEBUG
        char addrBuf[4];
        bytes2hex((unsigned char*)&addr, addrBuf, 2);
        char valBuf[2];
        bytes2hex((unsigned char*)&val, valBuf, 1);
        cout << "Memory 8 write: " << valBuf[0] << valBuf[1] << " | To: " << addrBuf[0] << addrBuf[1] << addrBuf[2] << addrBuf[3] << endl;
    #endif
    mem[addr] = val;
}

// LITTLE ENDIAN
void nes_mem::write_16(uint16_t addr, uint16_t val)
{
    #ifdef MEM_DEBUG
        char addr1Buf[4];
        bytes2hex((unsigned char*)&addr, addr1Buf, 2);
        char addr2Buf[4];
        uint16_t tempAddr = addr + 1;
        bytes2hex((unsigned char*)&tempAddr, addr2Buf, 2);
        char valBuf[4];
        bytes2hex((unsigned char*)&val, valBuf, 2);
        cout << "Memory 16 write: " << valBuf[0] << valBuf[1] << " | To: " << addr2Buf[0] << addr2Buf[1] << addr2Buf[2] << addr2Buf[3] << endl;
        cout << "               : " << valBuf[2] << valBuf[3] << " | To: " << addr1Buf[0] << addr1Buf[1] << addr1Buf[2] << addr1Buf[3] << endl;
    #endif
    mem[addr + 1] = (uint8_t)val;
    mem[addr] = (uint8_t)(val >> 8);
}

//--------------------Stack Access Functions--------------------//

uint8_t nes_mem::peek(uint8_t sp, uint8_t n)
{
    return mem[(0x0100 | sp) - n - 1];
}

uint8_t nes_mem::pop(uint8_t sp)
{
    return mem[0x0100 | sp];
}

void nes_mem::push(uint8_t sp, uint8_t val)
{
    mem[(0x100 | sp)] = val;
}

//--------------------ZPG Access Functions--------------------//

uint8_t nes_mem::readZPG_8(uint8_t addr)
{
    #ifdef MEM_DEBUG
        char buf[2];
        uint8_t temp = mem[addr];
        bytes2hex((unsigned char*)&temp, buf, 1);
        cout << "Memory 8 read: " << buf[0] << buf[1] << endl;
    #endif
    return mem[addr];
}

// LITTLE ENDIAN
uint16_t nes_mem::readZPG_16(uint8_t addr)
{
    #ifdef MEM_DEBUG
        char buf[4];
        uint16_t temp = (uint16_t)((mem[addr + 1] << 8) | mem[addr]);
        bytes2hex((unsigned char*)&temp, buf, 2);
        cout << "Memory 16 read: " << buf[0] << buf[1] << buf[2] << buf[3] << endl;
    #endif
    return (uint16_t)((mem[(uint8_t)(addr + 1)] << 8) | mem[addr]);
}

//--------------------ZPG Access Functions--------------------//

// LITTLE ENDIAN
uint16_t nes_mem::read_16_wrap(uint16_t addr)
{
    #ifdef MEM_DEBUG
        char buf[4];
        uint16_t temp = (uint16_t)((mem[addr + 1] << 8) | mem[addr]);
        bytes2hex((unsigned char*)&temp, buf, 2);
        cout << "Memory 16 read: " << buf[0] << buf[1] << buf[2] << buf[3] << endl;
    #endif
    uint8_t temp = (uint8_t)(addr & 0x00FF);
    temp++;
    uint16_t i2 = (uint16_t)((addr & 0xFF00) | temp);
    uint16_t toReturn = (uint16_t)((mem[i2] << 8) | mem[addr]);
    return toReturn;
}

//--------------------Debug Functions--------------------//

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
    for (int i = 0; i < sizeof(tempBuffer) / sizeof(char) / 2; i += 2)
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

void nes_mem::print_zpg(){
    cout << "ZERO PAGE : " << endl;
    char tempBuffer[0x200];
    bytes2hex(mem, tempBuffer, 0x100);
    for (int i = 0; i <= sizeof(tempBuffer) / sizeof(char); i += 2)
    {
        if (i % 0x100 == 0)
        //if ((i / 2) % 0x3C == 0)
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
    cout << endl << endl;
}

void nes_mem::print_stack(){
    cout << "STACK : " << endl;
    char tempBuffer[0x200];
    char temp[0x100];
    for(int i = 0; i < 0x100; i++){
        temp[i] = mem[0x100 & (uint8_t)i];
    }
    bytes2hex(temp, tempBuffer, 0x100);
    for (int i = 0; i <= sizeof(tempBuffer) / sizeof(char) - 1; i += 2)
    {
        if (i % 0x100 == 0)
        //if ((i / 2) % 0x3C == 0)
        {
            cout << endl;
            cout << std::hex << (0x100 | (i / 2)) << " : ";
        }
        else if (i % 8 == 0)
        {
            cout << " ";
        }
        cout << tempBuffer[i] << tempBuffer[i + 1] << " ";
    }
    cout << endl;
}