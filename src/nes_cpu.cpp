#include "../inc/nes_cpu.h"

using namespace std;

nes_cpu::nes_cpu()
{
    a = 0;
    x = 0;
    y = 0;
    status = 0;
    sp = 0;
    pc = 0;
    mem = nullptr;
    cout << "In CPU" << endl;
}

nes_cpu::~nes_cpu()
{
}

void nes_cpu::evaluate(uint8_t opcode)
{
    if (debug == 1)
    {
        cout << endl
             << "//----------CPU EVALUATE STARTING----------//" << endl;
        cout << "//-------------Before CPU State------------//" << endl;
        this->print_CPU_state();
    }

    // Actual Evaluate Code Goes Here
    switch (opcode)
    {
// ADC - Add With Carry
    case 0x69:
        // immediate
        break;
    case 0x65:
        // Zero Page
        break;
    case 0x75:
        // Zero Page X
        break;
    case 0x6D:
        // Absolute
        break;
    case 0x7D:
        // Absolute X
        break;
    case 0x79:
        // Abolute Y
        break;
    case 0x61:
        // Indirect X
        break;
    case 0x71:
        // Indirect Y
        break;
// AND - Logical AND
    case 0x29:
        // Immidiate
        break;
    case 0x25:
        // Zero Page
        break;
    case 0x35:
        // Zero Page X
        break;
    case 0x2D:
        // Absolute
        break;
    case 0x3D:
        // Absolute X
        break;
    case 0x39:
        // Absolute Y
        break;
    case 0x21:
        // Indirect X
        break;
    case 0x31:
        // Indirect Y
        break;
        // ASL - Arithmetic Shift Left
    case 0x41:
        //

    default:
        break;
    }

    if (debug == 1)
    {
        cout << "//-------------After CPU State-------------//" << endl;
        this->print_CPU_state();
    }
}

void nes_cpu::set_mem(nes_mem *_mem)
{
    mem = _mem;
}

void nes_cpu::set_debug(int val)
{
    debug = val;
}

void nes_cpu::bytes2hex(unsigned char *src, char *out, int len)
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

void nes_cpu::print_CPU_state()
{
    char buffer[7 * 2];
    unsigned char input[7] = {a, x, y, status, sp, (unsigned char)(pc >> 8), (unsigned char)pc};
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
// Source and destination are implied thus do not need any further operand
void nes_cpu::IMP()
{
    return;
}
// Accumulator
// Operate directly on the accumulator
uint8_t nes_cpu::ACC()
{
    return this->a;
}

// Immediate
// Directly specify an 8 bit constant within the instruction
uint8_t nes_cpu::IMM()
{
    return mem->read_8(pc++);
}

// Zero Page
// Access only the first 256 bytes of memory (0x0000 -> 0x00FF)
uint8_t nes_cpu::ZPG()
{
    // Get zero page address from instruction
    uint8_t temp = mem->read_8(pc++);

    // Make sure address lies between 0x00 and 0xFF
    // return value at this address in the zero page
    return mem->read_8(temp & 0xFF);
}

// Zero Page X
// Get the zero page address and add the value in the x register to it
uint8_t nes_cpu::ZPX()
{
    // Get zero page address from instruction
    // Add value in x register
    uint8_t temp = mem->read_8(pc++) + this->x;
    
    // Make sure address lies between 0x00 and 0xFF
    // return value at this address in the zero page
    return mem->read_8(temp & 0xFF);
}

// Zero Page Y
// Get the zero page address and add the value in the y register to it
uint8_t nes_cpu::ZPY()
{
    // Get zero page address from instruction
    // Add value in y register
    uint8_t temp = mem->read_8(pc++) + this->y;
    
    // Make sure address lies between 0x00 and 0xFF
    // return value at this address in the zero page
    return mem->read_8(temp & 0xFF);
}

// Relative
// Contains signed 8 bit offset relative to current address in program counter
int8_t nes_cpu::REL()
{
    // return the offset from memory
    return (int8_t)mem->read_8(pc++);
}

// Absolute
// Contains a full 16 bit address of target location
uint16_t nes_cpu::ABS()
{
    // Get the address from the instruction
    uint8_t toReturn = mem->read_16(pc);

    // Increment pc for each byte read (2)
    pc += 2;

    return toReturn;
}

// Absolute X
// Contains a 16 bit address with added offset from x register
uint16_t nes_cpu::ABX()
{
    // Get the address from the instruction and add value in x register
    uint16_t toReturn = mem->read_16(pc) + this->x;
    
    // Increment pc for each byte read (2)
    pc += 2;

    return toReturn;
}

// Absolute Y
// Contains a 16 bit address with added offset from y register
uint16_t nes_cpu::ABY()
{
    // Get the address from the instruction and add value in y register
    uint16_t toReturn = mem->read_16(pc) + this->y;
    
    // Increment pc for each byte read (2)
    pc += 2;

    return toReturn;
}

// Indirect
// Contains a 16 bit address - identifies the location of the least significant byte of another
uint16_t nes_cpu::IND()
{
    // Get the address from the instruction
    uint16_t toReturn = mem->read_16(mem->read_16(pc));

    // Increment pc for each byte read (2)
    pc += 2;

    return toReturn;
}

// Indexed Indirect
// Retreives 16 bit address located on zero page at address located in instruction plus x register value
uint16_t nes_cpu::IID()
{
    // Get the address for zero page from the instruction and add value in x register
    uint8_t temp = mem->read_8(pc++) + this->x;

    //return the address located in the zero page
    return mem->read_16(temp & 0xFF);
}

// Indirect Indexed
// Retreives 16 bit address located on zero page at address located in instruction plus y register value
uint16_t nes_cpu::IDI()
{
    // Get the zero page address from the instruction
    uint8_t temp = mem->read_8(pc++);
    
    // Get the target address from zero page and add value in y register
    return mem->read_16(temp) + this->y;
}
