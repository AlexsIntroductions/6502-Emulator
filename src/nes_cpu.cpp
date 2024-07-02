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
        // ---------------ADC - Add With Carry
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
        // ---------------AND - Logical AND
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
        // ---------------ASL - Arithmetic Shift Left
    case 0x0A:
        // Accumulator
        break;
    case 0x06:
        // Zero Page
        break;
    case 0x16:
        // Zero Page X
        break;
    case 0x0E:
        // Absolute
        break;
    case 0x1E:
        // Absolute X
        break;
        // ---------------BCC - Branch if Carry Clear
    case 0x90:
        // Relative
        break;
        // ---------------BCS - Branch if Carry Set
    case 0xB0:
        // Relative
        break;
        // ---------------BEQ - Branch if Equal
    case 0xF0:
        // Relative
        break;
        // ---------------BIT - Bit Test
    case 0x24:
        // Zero Page
        break;
    case 0x2C:
        // Absolute
        break;
        // ---------------BMI - Branch if Minus
    case 0x30:
        // Relative
        break;
        // ---------------BNE - Branch if Not Equal
    case 0xD0:
        // Relative
        break;
        // ---------------BPL - Branch if Positive
    case 0x10:
        // Relative
        break;
        // ---------------BRK - Force Interrupt
    case 0x00:
        // Implied
        break;
        // ---------------BVC - Branch if Overflow Set
    case 0x70:
        // Relative
        break;
        // ---------------CLC - Clear Carry Flag
    case 0x18:
        // Implied
        break;
        // ---------------CLD - Clear Decimal Mode
    case 0xD8:
        // Implied
        break;
        // ---------------CLI - Clear Interrupt Disable
    case 0x58:
        // Implied
        break;
        // ---------------CLV - Clear Overflow Flag
    case 0xB8:
        // Implied
        break;
        // ---------------CMP - Compare
    case 0xC9:
        // Immediate
        break;
    case 0xC5:
        // Zero Page
        break;
    case 0xD5:
        // Zero Page X
        break;
    case 0xCD:
        // Absolute
        break;
    case 0xDD:
        // Absolute X
        break;
    case 0xD9:
        // Absolute Y
        break;
    case 0xC1:
        // Indirect X
        break;
    case 0xD1:
        // Indirect Y
        break;
        // ---------------CPX - Compare X Register
    case 0xE0:
        // Immediate
        break;
    case 0xE4:
        // Zero Page
        break;
    case 0xEC:
        // Absolute
        break;
        // ---------------CPY - Compare Y Register
    case 0xC0:
        // Immediate
        break;
    case 0xC4:
        // Zero Page
        break;
    case 0xCC:
        // Absolute
        break;
        // ---------------DEC - Decrement Memory
    case 0xC6:
        // Zero Page
        break;
    case 0xD6:
        // Zero Page X
        break;
    case 0xCE:
        // Absolute
        break;
    case 0xDE:
        // Absolute X
        break;
        // ---------------DEX - Decrement X Register
    case 0xCA:
        // Implied
        break;
        // ---------------DEY - Decrement Y Register
    case 0x88:
        // Implied
        break;
        // ---------------EOR - Exclusive OR
    case 0x49:
        // Immediate
        break;
    case 0x45:
        // Zero Page
        break;
    case 0x55:
        // Zero Page X
        break;
    case 0x4D:
        // Absolute
        break;
    case 0x5D:
        // Absolute X
        break;
    case 0x59:
        // Absolue Y
        break;
    case 0x41:
        // Indirect X
        break;
    case 0x51:
        // Indirect Y
        break;
        // ---------------INC - Increment Memory
    case 0xE6:
        // Zero Page
        break;
    case 0xF6:
        // Zero Page X
        break;
    case 0xEE:
        // Absolute
        break;
    case 0xFE:
        // Absolute X
        break;
        // ---------------INX - Increment X Register
    case 0xE8:
        // Implied
        break;
        // ---------------INY - Increment Y Register
    case 0xC8:
        // Implied
        break;
        // ---------------JMP - Jump
    case 0x4C:
        // Absolute
        break;
    case 0x6C:
        // Indirect
        break;
        // ---------------JSR - Jump to Subroutine
    case 0x20:
        // Absolute
        break;
        // ---------------LDA - Load Accumulator
    case 0xA9:
        // Immediate
        break;
    case 0xA5:
        // Zero Page
        break;
    case 0xB5:
        // Zero Page X
        break;
    case 0xAD:
        // Absolute
        break;
    case 0xBD:
        // Absolute X
        break;
    case 0xB9:
        // Absolute Y
        break;
    case 0xA1:
        // Indirect X
        break;
    case 0xB1:
        // Indirect Y
        break;
        // ---------------LDX - Load X Register
    case 0xA2:
        // Immediate
        break;
    case 0xA6:
        // Zero Page
        break;
    case 0xB6:
        // Zero Page Y
        break;
    case 0xAE:
        // Absolute
        break;
    case 0xBE:
        // Absolute Y
        break;
        // ---------------LDY - Load Y Register
    case 0xA0:
        // Immediate
        break;
    case 0xA4:
        // Zero Page
        break;
    case 0xB4:
        // Zero Page X
        break;
    case 0xAC:
        // Absolute
        break;
    case 0xBC:
        // Absolute X
        break;
        // ---------------LSR - Logical Shift Right
    case 0x4A:
        // Accumulator
        break;
    case 0x46:
        // Zero Page
        break;
    case 0x56:
        // Zero Page X
        break;
    case 0x4E:
        // Absolute
        break;
    case 0x5E:
        // Absolute X
        break;
        // ---------------NOP - No Operation
    case 0xEA:
        // Implied
        break;
        // ---------------ORA - Logical Inclusive OR
    case 0x09:
        // Immediate
        break;
    case 0x05:
        // Zero Page
        break;
    case 0x15:
        // Zero Page X
        break;
    case 0x0D:
        // Absolute
        break;
    case 0x1D:
        // Absolute X
        break;
    case 0x19:
        // Absolute Y
        break;
    case 0x01:
        // Indirect X
        break;
    case 0x11:
        // Indirect Y
        break;
        // ---------------PHA - Push Accumulator
    case 0x48:
        // Implied
        break;
        // ---------------PHP - Push Processor Status
    case 0x08:
        // Implied
        break;
        // ---------------PLA - Pull Accumulator
    case 0x68:
        // Implied
        break;
        // ---------------PLP - Pull Processor Status
    case 0x28:
        // Implied
        break;
        // ---------------ROL - Rotate Left
    case 0x2A:
        // Accumulator
        break;
    case 0x26:
        // Zero Page
        break;
    case 0x36:
        // Zero Page X
        break;
    case 0x2E:
        // Absolute
        break;
    case 0x3E:
        // Absolute X
        break;
        // ---------------ROR - Rotate Right
    case 0x6A:
        // Accumulator
        break;
    case 0x66:
        // Zero Page
        break;
    case 0x76:
        // Zero Page X
        break;
    case 0x6E:
        // Absolute
        break;
    case 0x7E:
        // Absolute X
        break;
        // ---------------RTI - Return from Interrupt
    case 0x40:
        // Implied 
        break;
        // ---------------RTS - Return from Subroutine
    case 0x60:
        // Implied
        break;
        // ---------------SBC - Subtract with Carry
    case 0xE9:
        // Immediate
        break;
    case 0xE5:
        // Zero Page
        break;
    case 0xF5:
        // Zero Page X
        break;
    case 0xED:
        // Absolute
        break;
    case 0xFD:
        // Absolute X
        break;
    case 0xF9:
        // Absolute Y
        break;
    case 0xE1:
        // Indirect X
        break;
    case 0xF1:
        // Indirect Y
        break;
        // ---------------SEC - Set Carry Flag
    case 0x38:
        // Implied
        break;
        // ---------------SED - Set Decimal Flag
    case 0xF8:
        // Implied
        break;
        // ---------------SEI - Set Interrupt Disable
    case 0x78:
        // Implied
        break;
        // ---------------STA - Store Accumulator
    case 0x85:
        // Zero Page
        break;
    case 0x95:
        // Zero Page X
        break;
    case 0x8D:
        // Absolute
        break;
    case 0x9D:
        // Absolute X
        break;
    case 0x99:
        // Absolute Y
        break;
    case 0x81:
        // Indirect X
        break;
    case 0x91:
        // Indirect Y
        break;
        // ---------------STX - Store X Register
    case 0x86:
        // Zero Page
        break;
    case 0x96:
        // Zero Page Y
        break;
    case 0x8E:
        // Absolute 
        break;
        // ---------------STY - Store Y Register
    case 0x84:
        // Zero Page
        break;
    case 0x94:
        // Zero Page X
        break;
    case 0x8C:
        // Absolute
        break;
        // ---------------TAX - Transfer Accumulator to X
    case 0xAA:
        // Implied
        break;
        // ---------------TAY - Transfer Accumulator to Y
    case 0xA8:
        // Implied
        break;
        // ---------------TSX - Transfer Stack Pointer to X
    case 0xBA:
        // Implied 
        break;
        // ---------------TXA - Transfer X to Accumulator
    case 0x8A:
        // Implied
        break;
        // ---------------TXS - Transfer X to Stack Pointer
    case 0x9A:
        // Implied
        break;
        // ---------------TYA - Transfer Y to Accumulator
    case 0x98:
        // Implied
        break;
    default:
        cout << endl << "ERROR IN EVALUATE: INSTRUCTION NOT CODED FOR" << endl << endl;
        break;
    }

    if (debug == 1)
    {
        cout << "//-------------After CPU State-------------//" << endl;
        this->print_CPU_state();
        cout << endl
             << "END" << endl
             << endl;
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

    // return the address located in the zero page
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

//----------INSTRUCTION FUNCTIONS----------//
void nes_cpu::ADC()
{

}

void nes_cpu::AND() {}

void nes_cpu::ASL() {}

void nes_cpu::BCC() {}

void nes_cpu::BCS() {}

void nes_cpu::BEQ() {}

void nes_cpu::BIT() {}

void nes_cpu::BMI() {}

void nes_cpu::BNE() {}

void nes_cpu::BPL() {}

void nes_cpu::BRK() {}

void nes_cpu::BVC() {}

void nes_cpu::BVS() {}

void nes_cpu::CLC() {}

void nes_cpu::CLD() {}

void nes_cpu::CLI() {}

void nes_cpu::CLV() {}

void nes_cpu::CMP() {}

void nes_cpu::CPX() {}

void nes_cpu::CPY() {}

void nes_cpu::DEC() {}

void nes_cpu::DEX() {}

void nes_cpu::DEY() {}

void nes_cpu::EOR() {}

void nes_cpu::INC() {}

void nes_cpu::INX() {}

void nes_cpu::INY() {}

void nes_cpu::JMP() {}

void nes_cpu::JSR() {}

void nes_cpu::LDA() {}

void nes_cpu::LDX() {}

void nes_cpu::LDY() {}

void nes_cpu::LSR() {}

void nes_cpu::NOP() {}

void nes_cpu::ORA() {}

void nes_cpu::PHA() {}

void nes_cpu::PHP() {}

void nes_cpu::PLA() {}

void nes_cpu::PLP() {}

void nes_cpu::ROL() {}

void nes_cpu::ROR() {}

void nes_cpu::RTI() {}

void nes_cpu::RTS() {}

void nes_cpu::SBC() {}

void nes_cpu::SEC() {}

void nes_cpu::SED() {}

void nes_cpu::SEI() {}

void nes_cpu::STA() {}

void nes_cpu::STX() {}

void nes_cpu::STY() {}

void nes_cpu::TAX() {}

void nes_cpu::TAY() {}

void nes_cpu::TSX() {}

void nes_cpu::TXA() {}

void nes_cpu::TXS() {}

void nes_cpu::TYA() {}