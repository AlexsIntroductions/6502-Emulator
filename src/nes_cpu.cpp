#include "../inc/nes_cpu.h"
using namespace std;

char HexLookUp1[] = "0123456789abcdef";

nes_cpu::nes_cpu()
{
    a = 0;
    x = 0;
    y = 0;
    status = 0;
    sp = 0;
    pc = 0;
    _mem = nullptr;
}

nes_cpu::nes_cpu(nes_mem *_mem)
{
    a = 0;
    x = 0;
    y = 0;
    status = 0;
    sp = 0;
    pc = 0;
    this->_mem = _mem;
    cout << "In CPU" << endl;
}

nes_cpu::~nes_cpu()
{
}

void nes_cpu::evaluate(unsigned char opcode)
{

    //
    this->print_CPU_state();
}

void nes_cpu::bytes2hex(unsigned char *src, char *out, int len)
{
    while (len--)
    {
        *out++ = HexLookUp1[*src >> 4];
        *out++ = HexLookUp1[*src & 0x0F];
        src++;
    }
    *out = 0;
}

void nes_cpu::print_CPU_state()
{
    char buffer[7 * 2 + 1];
    unsigned char input[7] = {a, x, y, status, sp, (unsigned char)((pc >> 8) & 0xff), pc};
    bytes2hex(input, buffer, sizeof(input));
    cout << endl
         << endl
         << "CPU STATE:" << endl;
    cout << "-----------------------------------" << endl;
    for (int i = 0; i < sizeof(buffer) / sizeof(unsigned char); i += 2)
    {
        if (i == 0)
        {
            cout << "Accumulator  : " << buffer[i] << buffer[i + 1] << endl;
        }
        if (i == 2)
        {
            cout << "X            : " << buffer[i] << buffer[i + 1] << endl;
        }
        if (i == 4)
        {
            cout << "Y            : " << buffer[i] << buffer[i + 1] << endl;
        }
        if (i == 6)
        {
            cout << "Status Reg   : " << buffer[i] << buffer[i + 1] << endl;
        }
        if (i == 8)
        {
            cout << "Stack Pointer: " << buffer[i] << buffer[i + 1] << endl;
        }
        if (i == 10)
        {
            cout << "Program Count: " << buffer[i] << buffer[++i] << buffer[++i] << buffer[++i] << endl;
        }
    }
    cout << "-----------------------------------" << endl;
}

//----------ADDRESSING MODE FUNCTIONS----------//

/*-----------------------------------------------
Each function will be called before the instruction
functions so that the proper memory/value is being 
operated on.
-----------------------------------------------*/

// Implicit
    //implied directly by the function of the instruction itself
void *nes_cpu::IMP(){
    return nullptr;
}
// Accumulator
    //operate directly upon the accumulator
void *nes_cpu::ACC(){
    return *this->a;
}

// Immediate
    //directly specify an 8 bit constant within the instruction 
void *nes_cpu::IMM(){
    return nullptr;
}
// Zero Page
void *nes_cpu::ZPG(){
    return 
}

// Zero Page X
void *nes_cpu::ZPX();

// Zero Page Y
void *nes_cpu::ZPY();

// Relative
void *nes_cpu::REL();

// Absolute
void *nes_cpu::ABS();

// Absolute X
void *nes_cpu::ABX();

// Absolute Y
void *nes_cpu::ABY();

// Indirect
void *nes_cpu::IND();

// Indexed Indirect
void *nes_cpu::IID();

// Indirect Indexed
void *nes_cpu::IDI();

