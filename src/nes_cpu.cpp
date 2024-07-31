#include "../inc/nes_cpu.h"

using namespace std;
/**
 * NOTES:
 *  - Stack Pointer to 0xFF on start and reset
 */

nes_cpu::nes_cpu()
{
    a = 0;
    x = 0;
    y = 0;
    status = 0x24;
    sp = 0xFD;
    pc = 0;
    mem = nullptr;
    cout << "In CPU" << endl;
}

nes_cpu::~nes_cpu()
{
}

//--------------------Component Functions--------------------//

void nes_cpu::evaluate()
{

    #ifdef CPU_DEBUG
        cout << endl
             << "//--------------------CPU EVALUATE STARTING--------------------//" << endl << endl;
        cout << "//-------------Before CPU State------------//";
        this->print_CPU_state();
    #endif

    // The "Fetch-Execute cycle" is what drives a processor
    // The processor fetches an instruction and then executes it.
    // The Program Counter is incremented AFTER the Fetch phase and BEFORE the Execute phase.

    // Fetch Code Goes here

    // Get Current Instruction from Memory and Increment PC
    #ifdef CPU_LOG
        cpuLogger.SetPC(pc);
        cpuLogger.SetAcc(a);
        cpuLogger.SetX(x);
        cpuLogger.SetY(y);
        cpuLogger.SetStatus(status);
        cpuLogger.SetStackPointer(sp);
    #endif

    uint8_t opcode = mem->read_8(pc++);

    #ifdef CPU_LOG
        cpuLogger.SetOpcode(opcode);
        // if(pc - 1 == 0xDBB5){
        //     mem->print_mem();
        // }
    #endif

    #ifdef CPU_DEBUG
        char buf[2];
        bytes2hex((unsigned char*)&opcode, buf, 1);
        cout << "CURRENT OPCODE: " << buf[0] << buf[1] << endl << endl;

        char buffer[40];
        unsigned char input[20];
        for(int i = 0; i < 20; i++){
            input[i] = mem->read_8(pc - 10 + i);
        }
        bytes2hex(input, buffer, 20);

        cout << "LOCAL MEMORY:" << endl << endl;
        for(int i = 0; i < 40; i+=2){
            if(i == 18){
                cout << " | " << buffer[i] << buffer[i+1] << " | ";
            }
            else{
                cout << buffer[i] << buffer[i+1] << " ";
            }
        }
        cout << endl << endl;
    #endif
    
    // Execute Code Goes Here
    switch (opcode)
    {
        // ---------------ADC - Add With Carry
    case 0x69:
        // immediate
        ADC(IMM());
        break;
    case 0x65:
        // Zero Page
        ADC(ZPG_MEM());
        break;
    case 0x75:
        // Zero Page X
        ADC(ZPX_MEM());
        break;
    case 0x6D:
        // Absolute
        ADC(ABS_MEM());
        break;
    case 0x7D:
        // Absolute X
        ADC(ABX_MEM());
        break;
    case 0x79:
        // Abolute Y
        ADC(ABY_MEM());
        break;
    case 0x61:
        // Indirect X
        ADC(IID_MEM());
        break;
    case 0x71:
        // Indirect Y
        ADC(IDI_MEM());
        break;
        // ---------------AND - Logical AND
    case 0x29:
        // Immidiate
        AND(IMM());
        break;
    case 0x25:
        // Zero Page
        AND(ZPG_MEM());
        break;
    case 0x35:
        // Zero Page X
        AND(ZPX_MEM());
        break;
    case 0x2D:
        // Absolute
        AND(ABS_MEM());
        break;
    case 0x3D:
        // Absolute X
        AND(ABX_MEM());
        break;
    case 0x39:
        // Absolute Y
        AND(ABY_MEM());
        break;
    case 0x21:
        // Indirect X
        AND(IID_MEM());
        break;
    case 0x31:
        // Indirect Y
        AND(IDI_MEM());
        break;
        // ---------------ASL - Arithmetic Shift Left
    case 0x0A:
        // Accumulator
        ASL_ACC(ACC());
        break;
    case 0x06:
        // Zero Page
        ASL(ZPG());
        break;
    case 0x16:
        // Zero Page X
        ASL(ZPX());
        break;
    case 0x0E:
        // Absolute
        ASL(ABS());
        break;
    case 0x1E:
        // Absolute X
        ASL(ABX());
        break;
        // ---------------BCC - Branch if Carry Clear
    case 0x90:
        // Relative
        BCC(REL());
        break;
        // ---------------BCS - Branch if Carry Set
    case 0xB0:
        // Relative
        BCS(REL());
        break;
        // ---------------BEQ - Branch if Equal
    case 0xF0:
        // Relative
        BEQ(REL());
        break;
        // ---------------BIT - Bit Test
    case 0x24:
        // Zero Page
        BIT(ZPG_MEM());
        break;
    case 0x2C:
        // Absolute
        BIT(ABS_MEM());
        break;
        // ---------------BMI - Branch if Minus
    case 0x30:
        // Relative
        BMI(REL());
        break;
        // ---------------BNE - Branch if Not Equal
    case 0xD0:
        // Relative
        BNE(REL());
        break;
        // ---------------BPL - Branch if Positive
    case 0x10:
        // Relative
        BPL(REL());
        break;
        // ---------------BRK - Force Interrupt
    case 0x00:
        // Implied
        BRK(IMP());
        break;
        // ---------------BVC - Branch if Overflow Set
    case 0x50:
        // Relative
        BVC(REL());
        break;
        // ---------------BVC - Branch if Overflow Set
    case 0x70:
        // Relative
        BVS(REL());
        break;
        // ---------------CLC - Clear Carry Flag
    case 0x18:
        // Implied
        CLC(IMP());
        break;
        // ---------------CLD - Clear Decimal Mode
    case 0xD8:
        // Implied
        CLD(IMP());
        break;
        // ---------------CLI - Clear Interrupt Disable
    case 0x58:
        // Implied
        CLI(IMP());
        break;
        // ---------------CLV - Clear Overflow Flag
    case 0xB8:
        // Implied
        CLV(IMP());
        break;
        // ---------------CMP - Compare
    case 0xC9:
        // Immediate
        CMP(IMM());
        break;
    case 0xC5:
        // Zero Page
        CMP(ZPG_MEM());
        break;
    case 0xD5:
        // Zero Page X
        CMP(ZPX_MEM());
        break;
    case 0xCD:
        // Absolute
        CMP(ABS_MEM());
        break;
    case 0xDD:
        // Absolute X
        CMP(ABX_MEM());
        break;
    case 0xD9:
        // Absolute Y
        CMP(ABY_MEM());
        break;
    case 0xC1:
        // Indirect X
        CMP(IID_MEM());
        break;
    case 0xD1:
        // Indirect Y
        CMP(IDI_MEM());
        break;
        // ---------------CPX - Compare X Register
    case 0xE0:
        // Immediate
        CPX(IMM());
        break;
    case 0xE4:
        // Zero Page
        CPX(ZPG_MEM());
        break;
    case 0xEC:
        // Absolute
        CPX(ABS_MEM());
        break;
        // ---------------CPY - Compare Y Register
    case 0xC0:
        // Immediate
        CPY(IMM());
        break;
    case 0xC4:
        // Zero Page
        CPY(ZPG_MEM());
        break;
    case 0xCC:
        // Absolute
        CPY(ABS_MEM());
        break;
        // ---------------DEC - Decrement Memory
    case 0xC6:
        // Zero Page
        DEC(ZPG());
        break;
    case 0xD6:
        // Zero Page X
        DEC(ZPX());
        break;
    case 0xCE:
        // Absolute
        DEC(ABS());
        break;
    case 0xDE:
        // Absolute X
        DEC(ABX());
        break;
        // ---------------DEX - Decrement X Register
    case 0xCA:
        // Implied
        DEX(IMP());
        break;
        // ---------------DEY - Decrement Y Register
    case 0x88:
        // Implied
        DEY(IMP());
        break;
        // ---------------EOR - Exclusive OR
    case 0x49:
        // Immediate
        EOR(IMM());
        break;
    case 0x45:
        // Zero Page
        EOR(ZPG_MEM());
        break;
    case 0x55:
        // Zero Page X
        EOR(ZPX_MEM());
        break;
    case 0x4D:
        // Absolute
        EOR(ABS_MEM());
        break;
    case 0x5D:
        // Absolute X
        EOR(ABX_MEM());
        break;
    case 0x59:
        // Absolue Y
        EOR(ABY_MEM());
        break;
    case 0x41:
        // Indirect X
        EOR(IID_MEM());
        break;
    case 0x51:
        // Indirect Y
        EOR(IDI_MEM());
        break;
        // ---------------INC - Increment Memory
    case 0xE6:
        // Zero Page
        INC(ZPG());
        break;
    case 0xF6:
        // Zero Page X
        INC(ZPX());
        break;
    case 0xEE:
        // Absolute
        INC(ABS());
        break;
    case 0xFE:
        // Absolute X
        INC(ABX());
        break;
        // ---------------INX - Increment X Register
    case 0xE8:
        // Implied
        INX(IMP());
        break;
        // ---------------INY - Increment Y Register
    case 0xC8:
        // Implied
        INY(IMP());
        break;
        // ---------------JMP - Jump
    case 0x4C:
        // Absolute
        JMP(JMP_ABS());
        break;
    case 0x6C:
        // Indirect
        JMP(IND());
        break;
        // ---------------JSR - Jump to Subroutine
    case 0x20:
        // Absolute
        JSR(JMP_ABS());
        break;
        // ---------------LDA - Load Accumulator
    case 0xA9:
        // Immediate
        LDA(IMM());
        break;
    case 0xA5:
        // Zero Page
        LDA(ZPG_MEM());
        break;
    case 0xB5:
        // Zero Page X
        LDA(ZPX_MEM());
        break;
    case 0xAD:
        // Absolute
        LDA(ABS_MEM());
        break;
    case 0xBD:
        // Absolute X
        LDA(ABX_MEM());
        break;
    case 0xB9:
        // Absolute Y
        LDA(ABY_MEM());
        break;
    case 0xA1:
        // Indirect X
        LDA(IID_MEM());
        break;
    case 0xB1:
        // Indirect Y
        LDA(IDI_MEM());
        break;
        // ---------------LDX - Load X Register
    case 0xA2:
        // Immediate
        LDX(IMM());
        break;
    case 0xA6:
        // Zero Page
        LDX(ZPG_MEM());
        break;
    case 0xB6:
        // Zero Page Y
        LDX(ZPY_MEM());
        break;
    case 0xAE:
        // Absolute
        LDX(ABS_MEM());
        break;
    case 0xBE:
        // Absolute Y
        LDX(ABY_MEM());
        break;
        // ---------------LDY - Load Y Register
    case 0xA0:
        // Immediate
        LDY(IMM());
        break;
    case 0xA4:
        // Zero Page
        LDY(ZPG_MEM());
        break;
    case 0xB4:
        // Zero Page X
        LDY(ZPX_MEM());
        break;
    case 0xAC:
        // Absolute
        LDY(ABS_MEM());
        break;
    case 0xBC:
        // Absolute X
        LDY(ABX_MEM());
        break;
        // ---------------LSR - Logical Shift Right
    case 0x4A:
        // Accumulator
        LSR_ACC(ACC());
        break;
    case 0x46:
        // Zero Page
        LSR(ZPG());
        break;
    case 0x56:
        // Zero Page X
        LSR(ZPX());
        break;
    case 0x4E:
        // Absolute
        LSR(ABS());
        break;
    case 0x5E:
        // Absolute X
        LSR(ABX());
        break;
        // ---------------NOP - No Operation
    case 0xEA:
        // Implied
        NOP(IMP());
        break;
        // ---------------ORA - Logical Inclusive OR
    case 0x09:
        // Immediate
        ORA(IMM());
        break;
    case 0x05:
        // Zero Page
        ORA(ZPG_MEM());
        break;
    case 0x15:
        // Zero Page X
        ORA(ZPX_MEM());
        break;
    case 0x0D:
        // Absolute
        ORA(ABS_MEM());
        break;
    case 0x1D:
        // Absolute X
        ORA(ABX_MEM());
        break;
    case 0x19:
        // Absolute Y
        ORA(ABY_MEM());
        break;
    case 0x01:
        // Indirect X
        ORA(IID_MEM());
        break;
    case 0x11:
        // Indirect Y
        ORA(IDI_MEM());
        break;
        // ---------------PHA - Push Accumulator
    case 0x48:
        // Implied
        PHA(IMP());
        break;
        // ---------------PHP - Push Processor Status
    case 0x08:
        // Implied
        PHP(IMP());
        break;
        // ---------------PLA - Pull Accumulator
    case 0x68:
        // Implied
        PLA(IMP());
        break;
        // ---------------PLP - Pull Processor Status
    case 0x28:
        // Implied
        PLP(IMP());
        break;
        // ---------------ROL - Rotate Left
    case 0x2A:
        // Accumulator
        ROL_ACC(ACC());
        break;
    case 0x26:
        // Zero Page
        ROL(ZPG());
        break;
    case 0x36:
        // Zero Page X
        ROL(ZPX());
        break;
    case 0x2E:
        // Absolute
        ROL(ABS());
        break;
    case 0x3E:
        // Absolute X
        ROL(ABX());
        break;
        // ---------------ROR - Rotate Right
    case 0x6A:
        // Accumulator
        ROR_ACC(ACC());
        break;
    case 0x66:
        // Zero Page
        ROR(ZPG());
        break;
    case 0x76:
        // Zero Page X
        ROR(ZPX());
        break;
    case 0x6E:
        // Absolute
        ROR(ABS());
        break;
    case 0x7E:
        // Absolute X
        ROR(ABX());
        break;
        // ---------------RTI - Return from Interrupt
    case 0x40:
        // Implied
        RTI(IMP());
        break;
        // ---------------RTS - Return from Subroutine
    case 0x60:
        // Implied
        RTS(IMP());
        break;
        // ---------------SBC - Subtract with Carry
    case 0xE9:
        // Immediate
        SBC(IMM());
        break;
    case 0xE5:
        // Zero Page
        SBC(ZPG_MEM());
        break;
    case 0xF5:
        // Zero Page X
        SBC(ZPX_MEM());
        break;
    case 0xED:
        // Absolute
        SBC(ABS_MEM());
        break;
    case 0xFD:
        // Absolute X
        SBC(ABX_MEM());
        break;
    case 0xF9:
        // Absolute Y
        SBC(ABY_MEM());
        break;
    case 0xE1:
        // Indirect X
        SBC(IID_MEM());
        break;
    case 0xF1:
        // Indirect Y
        SBC(IDI_MEM());
        break;
        // ---------------SEC - Set Carry Flag
    case 0x38:
        // Implied
        SEC(IMP());
        break;
        // ---------------SED - Set Decimal Flag
    case 0xF8:
        // Implied
        SED(IMP());
        break;
        // ---------------SEI - Set Interrupt Disable
    case 0x78:
        // Implied
        SEI(IMP());
        break;
        // ---------------STA - Store Accumulator
    case 0x85:
        // Zero Page
        STA(ZPG());
        break;
    case 0x95:
        // Zero Page X
        STA(ZPX());
        break;
    case 0x8D:
        // Absolute
        STA(ABS());
        break;
    case 0x9D:
        // Absolute X
        STA(ABX());
        break;
    case 0x99:
        // Absolute Y
        STA(ABY());
        break;
    case 0x81:
        // Indirect X
        STA(IID());
        break;
    case 0x91:
        // Indirect Y
        STA(IDI());
        break;
        // ---------------STX - Store X Register
    case 0x86:
        // Zero Page
        STX(ZPG());
        break;
    case 0x96:
        // Zero Page Y
        STX(ZPY());
        break;
    case 0x8E:
        // Absolute
        STX(ABS());
        break;
        // ---------------STY - Store Y Register
    case 0x84:
        // Zero Page
        STY(ZPG());
        break;
    case 0x94:
        // Zero Page X
        STY(ZPX());
        break;
    case 0x8C:
        // Absolute
        STY(ABS());
        break;
        // ---------------TAX - Transfer Accumulator to X
    case 0xAA:
        // Implied
        TAX(IMP());
        break;
        // ---------------TAY - Transfer Accumulator to Y
    case 0xA8:
        // Implied
        TAY(IMP());
        break;
        // ---------------TSX - Transfer Stack Pointer to X
    case 0xBA:
        // Implied
        TSX(IMP());
        break;
        // ---------------TXA - Transfer X to Accumulator
    case 0x8A:
        // Implied
        TXA(IMP());
        break;
        // ---------------TXS - Transfer X to Stack Pointer
    case 0x9A:
        // Implied
        TXS(IMP());
        break;
        // ---------------TYA - Transfer Y to Accumulator
    case 0x98:
        // Implied
        TYA(IMP());
        break;
    default:

        #ifdef CPU_DEBUG
        cout << endl
             << "ERROR IN EVALUATE: INSTRUCTION NOT CODED FOR" << endl
             << endl;
        #endif

        #ifdef CPU_LOG
            cpuLogger.SetInstructionName("???");
        #endif
        pc++;
        break;
    }

    #ifdef CPU_DEBUG
        cout << endl << "//-------------After CPU State-------------//";
        this->print_CPU_state();
        cout << endl;
        mem->print_zpg();
    #endif
    
    #ifdef CPU_LOG
        cpuLogger.Log();
    #endif
}

void nes_cpu::set_mem(nes_mem *_mem)
{
    mem = _mem;
    // mem->print_mem();
}

void nes_cpu::set_pc(uint16_t address){
    pc = address;
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
    cout << endl;
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
            cout << "Program Count: " << buffer[i++] << buffer[i++] << buffer[i++] << buffer[i] << endl;
        }
    }
    cout << "-----------------------------------" << endl;
}

//--------------------ADDRESSING MODE FUNCTIONS--------------------//

/*-----------------------------------------------
Each function will be called before the instruction
functions so that the proper memory/value is being
operated on.
-----------------------------------------------*/

// Implied
// Source and destination are implied thus do not need any further operand
uint16_t nes_cpu::IMP()
{
    #ifdef CPU_DEBUG
        cout << "ADDRESSING MODE: IMPLIED" << endl;
    #endif

    return 0;
}

// Accumulator
// Operate directly on the accumulator
uint16_t nes_cpu::ACC()
{
    #ifdef CPU_DEBUG
        char buf[2];
        bytes2hex((unsigned char*)&a, buf, 1);
        cout << "ADDRESSING MODE: ACCUMULATOR | VALUE: " << buf[0] << buf[1] << endl;
    #endif

    return a;
}

// Immediate
// Directly specify an 8 bit constant within the instruction
uint16_t nes_cpu::IMM()
{
    uint8_t temp = mem->read_8(pc++);

    #ifdef CPU_DEBUG
        char buf[2];
        bytes2hex((unsigned char*)&temp, buf, 1);
        cout << "ADDRESSING MODE: IMMEDIATE | VALUE: " << buf[0] << buf[1] << endl;
    #endif

    #ifdef CPU_LOG
        cpuLogger.SetAddressingMode_8(temp, 0, 0, 0);
    #endif

    return temp;
}

// Zero Page
// Access only the first 256 bytes of memory (0x0000 -> 0x00FF)
uint16_t nes_cpu::ZPG()
{
    // Get zero page address from instruction
    uint8_t temp = mem->read_8(pc++);
    
    #ifdef CPU_DEBUG
        uint8_t tempVal = mem->read_8(temp);
        char buf[2];
        bytes2hex((unsigned char*)&temp, buf, 1);
        char buf2[2];
        bytes2hex((unsigned char*)&tempVal, buf2, 1);
        cout << "ADDRESSING MODE: ZERO PAGE | ADDRESS " << buf[0] << buf[1] << " | VALUE: " << buf2[0] << buf2[1] << endl;
    #endif

    #ifdef CPU_LOG
        cpuLogger.SetAddressingMode_8(temp, mem->read_8(temp), 0, 1);
    #endif

    // return address in the zero page
    return temp;
}
uint16_t nes_cpu::ZPG_MEM()
{
    // Get zero page address from instruction
    uint8_t temp = mem->read_8(pc++);
    
    #ifdef CPU_DEBUG
        uint8_t tempVal = mem->read_8(temp);
        char buf[2];
        bytes2hex((unsigned char*)&temp, buf, 1);
        char buf2[2];
        bytes2hex((unsigned char*)&tempVal, buf2, 1);
        cout << "ADDRESSING MODE: ZERO PAGE | ADDRESS " << buf[0] << buf[1] << " | VALUE: " << buf2[0] << buf2[1] << endl;
    #endif

    #ifdef CPU_LOG
        cpuLogger.SetAddressingMode_8(temp, mem->read_8(temp), 0, 1);
    #endif

    // return address in the zero page
    return mem->read_8(temp);
}

// Zero Page X
// Get the zero page address and add the value in the x register to it
uint16_t nes_cpu::ZPX()
{
    // Get zero page address from instruction
    // Add value in x register
    uint8_t temp = mem->read_8(pc++) + this->x;

    #ifdef CPU_DEBUG
        int8_t tempVal = mem->read_8(temp);
        char buf[2];
        bytes2hex((unsigned char*)&temp, buf, 1);
        char buf2[2];
        bytes2hex((unsigned char*)&tempVal, buf2, 1);
        cout << "ADDRESSING MODE: ZERO PAGE X | ADDRESS " << buf[0] << buf[1] << " | VALUE: " << buf2[0] << buf2[1] << endl;
    #endif

    #ifdef CPU_LOG
        cpuLogger.SetAddressingMode_8(temp - this->x, mem->read_8(temp), temp, 4);
    #endif

    // Make sure address lies between 0x00 and 0xFF
    // return value at this address in the zero page
    return temp & 0xFF;
}
uint16_t nes_cpu::ZPX_MEM()
{
    // Get zero page address from instruction
    // Add value in x register
    uint8_t temp = mem->read_8(pc++) + this->x;

    #ifdef CPU_DEBUG
        int8_t tempVal = mem->read_8(temp);
        char buf[2];
        bytes2hex((unsigned char*)&temp, buf, 1);
        char buf2[2];
        bytes2hex((unsigned char*)&tempVal, buf2, 1);
        cout << "ADDRESSING MODE: ZERO PAGE X | ADDRESS " << buf[0] << buf[1] << " | VALUE: " << buf2[0] << buf2[1] << endl;
    #endif

    #ifdef CPU_LOG
        cpuLogger.SetAddressingMode_8(temp - this->x, mem->read_8(temp), temp, 4);
    #endif

    // Make sure address lies between 0x00 and 0xFF
    // return value at this address in the zero page
    return mem->read_8(temp & 0xFF);
}

// Zero Page Y
// Get the zero page address and add the value in the y register to it
uint16_t nes_cpu::ZPY()
{
    // Get zero page address from instruction
    // Add value in y register
    uint8_t temp = mem->read_8(pc++) + this->y;

    #ifdef CPU_DEBUG
        uint8_t tempVal = mem->read_8(temp);
        char buf[2];
        bytes2hex((unsigned char*)&temp, buf, 1);
        char buf2[2];
        bytes2hex((unsigned char*)&tempVal, buf2, 1);
        cout << "ADDRESSING MODE: ZERO PAGE Y | ADDRESS " << buf[0] << buf[1] << " | VALUE: " << buf2[0] << buf2[1] << endl;
    #endif

    #ifdef CPU_LOG
        cpuLogger.SetAddressingMode_8(temp, mem->read_8(temp), temp - this->y, 5);
    #endif

    // Make sure address lies between 0x00 and 0xFF
    // return value at this address in the zero page
    return temp & 0xFF;
}
uint16_t nes_cpu::ZPY_MEM()
{
    // Get zero page address from instruction
    // Add value in y register
    uint8_t temp = mem->read_8(pc++) + this->y;

    #ifdef CPU_DEBUG
        uint8_t tempVal = mem->read_8(temp);
        char buf[2];
        bytes2hex((unsigned char*)&temp, buf, 1);
        char buf2[2];
        bytes2hex((unsigned char*)&tempVal, buf2, 1);
        cout << "ADDRESSING MODE: ZERO PAGE Y | ADDRESS " << buf[0] << buf[1] << " | VALUE: " << buf2[0] << buf2[1] << endl;
    #endif

    #ifdef CPU_LOG
        cpuLogger.SetAddressingMode_8(temp, mem->read_8(temp), temp - this->y, 5);
    #endif

    // Make sure address lies between 0x00 and 0xFF
    // return value at this address in the zero page
    return mem->read_8(temp & 0xFF);
}

// Relative
// Contains signed 8 bit offset relative to current address in program counter
uint16_t nes_cpu::REL()
{
    uint8_t temp = mem->read_8(pc++);
    // return the offset from memory
    #ifdef CPU_DEBUG
        char buf[2];
        bytes2hex((unsigned char*)&temp, buf, 1);
        cout << "ADDRESSING MODE: RELATIVE | SIGNED OFFSET " << buf[0] << buf[1] << endl;
    #endif

    #ifdef CPU_LOG
        cpuLogger.SetAddressingMode_8(temp, pc, 0, 2);
    #endif

    return temp;
}

// Absolute
// Reads a full 16 bit address of target location
uint16_t nes_cpu::ABS()
{
    // Get the address from the instruction
    uint16_t toReturn = mem->read_16(pc);

    #ifdef CPU_DEBUG
        char buf[4];
        bytes2hex((unsigned char*)&toReturn, buf, 2);
        uint8_t tempVal = mem->read_8(toReturn);
        char buf2[2];
        bytes2hex((unsigned char*)&tempVal, buf2, 1);
        cout << "ADDRESSING MODE: ABSOLUTE | ADDRESS " << buf[0] << buf[1] << buf[2] << buf[3] << " | VALUE: " << buf2[0] << buf2[1] << endl;
    #endif

    #ifdef CPU_LOG
        cpuLogger.SetAddressingMode_16(toReturn, mem->read_8(toReturn), 0, 1);
    #endif

    // Increment pc for each byte read (2)
    pc += 2;

    return toReturn;
}
uint16_t nes_cpu::ABS_MEM()
{
    // Get the address from the instruction
    uint16_t toReturn = mem->read_16(pc);

    #ifdef CPU_DEBUG
        char buf[4];
        bytes2hex((unsigned char*)&toReturn, buf, 2);
        uint8_t tempVal = mem->read_8(toReturn);
        char buf2[2];
        bytes2hex((unsigned char*)&tempVal, buf2, 1);
        cout << "ADDRESSING MODE: ABSOLUTE | ADDRESS " << buf[0] << buf[1] << buf[2] << buf[3] << " | VALUE: " << buf2[0] << buf2[1] << endl;
    #endif

    #ifdef CPU_LOG
        cpuLogger.SetAddressingMode_16(toReturn, mem->read_8(toReturn), 0, 1);
    #endif

    // Increment pc for each byte read (2)
    pc += 2;

    return mem->read_8(toReturn);
}

// Reads a full 16 bit address of target location
uint16_t nes_cpu::JMP_ABS()
{
    // Get the address from the instruction
    uint16_t toReturn = mem->read_16(pc);

    #ifdef CPU_DEBUG
        char buf[4];
        bytes2hex((unsigned char*)&toReturn, buf, 2);
        uint8_t tempVal = mem->read_8(toReturn);
        char buf2[2];
        bytes2hex((unsigned char*)&tempVal, buf2, 1);
        cout << "ADDRESSING MODE: ABSOLUTE | ADDRESS " << buf[0] << buf[1] << buf[2] << buf[3] << " | VALUE: " << buf2[0] << buf2[1] << endl;
    #endif

    #ifdef CPU_LOG
        cpuLogger.SetAddressingMode_16(toReturn, 0, 0, 0);
    #endif

    // Increment pc for each byte read (2)
    pc += 2;

    return toReturn;
}

// Absolute X
// Contains a 16 bit address with added offset from x register
uint16_t nes_cpu::ABX()
{
    // Get the address from the instruction and add value in x register
    uint16_t temp = mem->read_16(pc);
    uint16_t toReturn = (temp + this->x);

    #ifdef CPU_DEBUG
        char buf[4];
        bytes2hex((unsigned char*)&toReturn, buf, 2);
        uint8_t tempVal = mem->read_8(toReturn);
        char buf2[2];
        bytes2hex((unsigned char*)&tempVal, buf2, 1);
        cout << "ADDRESSING MODE: ABSOLUTE X | ADDRESS " << buf[0] << buf[1] << buf[2] << buf[3] << " | VALUE: " << buf2[0] << buf2[1] << endl;
    #endif

    #ifdef CPU_LOG
        cpuLogger.SetAddressingMode_16(toReturn, temp, mem->read_8(toReturn), 6);
    #endif

    // Increment pc for each byte read (2)
    pc += 2;

    return toReturn & 0xFFFF;
}
uint16_t nes_cpu::ABX_MEM()
{
    // Get the address from the instruction and add value in x register
    uint16_t temp = mem->read_16(pc);
    uint16_t toReturn = (temp + this->x);

    #ifdef CPU_DEBUG
        char buf[4];
        bytes2hex((unsigned char*)&toReturn, buf, 2);
        uint8_t tempVal = mem->read_8(toReturn);
        char buf2[2];
        bytes2hex((unsigned char*)&tempVal, buf2, 1);
        cout << "ADDRESSING MODE: ABSOLUTE X | ADDRESS " << buf[0] << buf[1] << buf[2] << buf[3] << " | VALUE: " << buf2[0] << buf2[1] << endl;
    #endif

    #ifdef CPU_LOG
        cpuLogger.SetAddressingMode_16(toReturn, temp, mem->read_8(toReturn), 6);
    #endif

    // Increment pc for each byte read (2)
    pc += 2;

    return mem->read_8(toReturn & 0xFFFF);
}

// Absolute Y
// Reads a 16 bit address with added offset from y register
uint16_t nes_cpu::ABY()
{
    // Get the address from the instruction and add value in y register
    uint16_t temp = mem->read_16(pc);
    uint16_t toReturn = (temp + this->y);

    #ifdef CPU_DEBUG
        char buf[4];
        bytes2hex((unsigned char*)&toReturn, buf, 2);
        uint8_t tempVal = mem->read_8(toReturn);
        char buf2[2];
        bytes2hex((unsigned char*)&tempVal, buf2, 1);
        cout << "ADDRESSING MODE: ABSOLUTE Y | ADDRESS " << buf[0] << buf[1] << buf[2] << buf[3] << " | VALUE: " << buf2[0] << buf2[1] << endl;
    #endif

    #ifdef CPU_LOG
        cpuLogger.SetAddressingMode_16(toReturn, temp, mem->read_8(toReturn), 5);
    #endif

    // Increment pc for each byte read (2)
    pc += 2;

    return toReturn & 0xFFFF;
}
uint16_t nes_cpu::ABY_MEM()
{
    // Get the address from the instruction and add value in y register
    uint16_t temp = mem->read_16(pc);
    uint16_t toReturn = (temp + this->y);

    #ifdef CPU_DEBUG
        char buf[4];
        bytes2hex((unsigned char*)&toReturn, buf, 2);
        uint8_t tempVal = mem->read_8(toReturn);
        char buf2[2];
        bytes2hex((unsigned char*)&tempVal, buf2, 1);
        cout << "ADDRESSING MODE: ABSOLUTE Y | ADDRESS " << buf[0] << buf[1] << buf[2] << buf[3] << " | VALUE: " << buf2[0] << buf2[1] << endl;
    #endif

    #ifdef CPU_LOG
        cpuLogger.SetAddressingMode_16(toReturn, temp, mem->read_8(toReturn), 5);
    #endif

    // Increment pc for each byte read (2)
    pc += 2;

    return mem->read_8(toReturn & 0xFFFF);
}

// Indirect
// Retreives a 16 bit address - identifies the location of the least significant byte of another
uint16_t nes_cpu::IND()
{
    // Get the address from the instruction
    uint16_t temp = mem->read_16(pc);
    uint16_t toReturn = mem->read_16_wrap(temp);

    #ifdef CPU_DEBUG
        char buf[4];
        bytes2hex((unsigned char*)&toReturn, buf, 2);
        cout << "ADDRESSING MODE: INDIRECT | ADDRESS " << buf[0] << buf[1] << buf[2] << buf[3]<< endl;
    #endif

    #ifdef CPU_LOG
        cpuLogger.SetAddressingMode_16(toReturn, temp, 0, 4);
    #endif

    pc += 2;

    return toReturn;
}

// Indexed Indirect (Indirect X)
// Retreives 16 bit address located on zero page at address located in instruction plus x register value
uint16_t nes_cpu::IID()
{
    // Get the address for zero page from the instruction and add value in x register
    uint8_t zpAdd = mem->read_8(pc++);
    uint16_t toReturn = mem->readZPG_16((uint8_t)(zpAdd + this->x) & 0xFF);

    #ifdef CPU_DEBUG
        char buf[4];
        bytes2hex((unsigned char*)&toReturn, buf, 2);
        uint8_t tempVal = mem->read_8(toReturn);
        char buf2[2];
        bytes2hex((unsigned char*)&tempVal, buf2, 1);
        cout << "ADDRESSING MODE: INDIRECT X | ADDRESS " << buf[0] << buf[1] << buf[2] << buf[3] << " | VALUE: " << buf2[0] << buf2[1] << endl;
    #endif

    #ifdef CPU_LOG
        uint8_t temp = mem->read_8(toReturn);
        cpuLogger.SetAddressingMode_16(toReturn, (uint16_t)((temp << 8) | zpAdd), (uint16_t)zpAdd + this->x, 2);
    #endif

    // return the address located in the zero page
    return toReturn;
}
uint16_t nes_cpu::IID_MEM()
{
    // Get the address for zero page from the instruction and add value in x register
    uint8_t zpAdd = mem->read_8(pc++);
    uint16_t toReturn = mem->readZPG_16((uint8_t)(zpAdd + this->x) & 0xFF);

    #ifdef CPU_DEBUG
        char buf[4];
        bytes2hex((unsigned char*)&toReturn, buf, 2);
        uint8_t tempVal = mem->read_8(toReturn);
        char buf2[2];
        bytes2hex((unsigned char*)&tempVal, buf2, 1);
        cout << "ADDRESSING MODE: INDIRECT X | ADDRESS " << buf[0] << buf[1] << buf[2] << buf[3] << " | VALUE: " << buf2[0] << buf2[1] << endl;
    #endif

    #ifdef CPU_LOG
        uint8_t temp = mem->read_8(toReturn);
        cpuLogger.SetAddressingMode_16(toReturn, (uint16_t)((temp << 8) | zpAdd), (uint16_t)zpAdd + this->x, 2);
    #endif

    // return the address located in the zero page
    return mem->read_8(toReturn);
}

// Indirect Indexed (Indirect Y)
// Retreives 16 bit address located on zero page at address located in instruction plus y register value
uint16_t nes_cpu::IDI()
{
    // Get the zero page address from the instruction
    uint8_t temp = mem->read_8(pc++);
    uint16_t toReturn = mem->readZPG_16(temp) + this->y;

    #ifdef CPU_DEBUG
        char buf[4];
        bytes2hex((unsigned char*)&toReturn, buf, 2);
        uint8_t tempVal = mem->read_8(toReturn);
        char buf2[2];
        bytes2hex((unsigned char*)&tempVal, buf2, 1);
        cout << "ADDRESSING MODE: INDIRECT Y | ADDRESS " << buf[0] << buf[1] << buf[2] << buf[3] << " | VALUE: " << buf2[0] << buf2[1] << endl;
    #endif

    #ifdef CPU_LOG
        cpuLogger.SetAddressingMode_16(toReturn, (uint16_t)((temp << 8) | mem->read_8(toReturn)), toReturn - this->y, 3);
    #endif

    // Get the target address from zero page and add value in y register
    return toReturn & 0xFFFF;
}
uint16_t nes_cpu::IDI_MEM()
{
    // Get the zero page address from the instruction
    uint8_t temp = mem->read_8(pc++);
    uint16_t toReturn = mem->readZPG_16(temp) + this->y;

    #ifdef CPU_DEBUG
        char buf[4];
        bytes2hex((unsigned char*)&toReturn, buf, 2);
        uint8_t tempVal = mem->read_8(toReturn);
        char buf2[2];
        bytes2hex((unsigned char*)&tempVal, buf2, 1);
        cout << "ADDRESSING MODE: INDIRECT Y | ADDRESS " << buf[0] << buf[1] << buf[2] << buf[3] << " | VALUE: " << buf2[0] << buf2[1] << endl;
    #endif

    #ifdef CPU_LOG
        cpuLogger.SetAddressingMode_16(toReturn, (uint16_t)((temp << 8) | mem->read_8(toReturn)), toReturn - this->y, 3);
    #endif

    // Get the target address from zero page and add value in y register
    return mem->read_8(toReturn & 0xFFFF);
}

//--------------------INSTRUCTION FUNCTIONS--------------------//

// ADC - Add with Carry
void nes_cpu::ADC(uint16_t val)
{
    // NOTE: Decimal Mode Not Implemented, NES Doesn't use Decimal Mode
    // Implement in future for accurate 6502 emulator

    #ifdef CPU_DEBUG
        cout << "ADC:" << endl;
    #endif
    
    #ifdef CPU_LOG
        cpuLogger.SetInstructionName("ADC");
    #endif

    // Add the accumulator, mem value, and carry into temp
    uint16_t temp = a + val + (uint8_t)(status & C_FLAG);

    // Check Carry Flag
    (temp >> 8) ? (status |= C_FLAG) : (status &= C_FLAG_INV);

    // Check Negative Flag
    (temp & 0x0080) ? (status |= N_FLAG) : (status &= N_FLAG_INV);

    // Check Overflow Flag | Formula for Calculating the Overflow Flag Taken from https://www.righto.com/2012/12/the-6502-overflow-flag-explained.html
    uint8_t c6 = (((a & 0b01111111) + (val & 0b01111111) + (status & C_FLAG)) & 0x80);
    ( (~(a & 0x80) & ~(val & 0x80) & c6) | ((a & 0x80) & (val & 0x80) & ~c6)) ? (status |= V_FLAG) : (status &= V_FLAG_INV);

    // Check Zero Flag
    ((uint8_t)(temp & 0x00FF) == 0) ? (status |= Z_FLAG) : (status &= Z_FLAG_INV);

    // Set Accumulator to new value
    a = (uint8_t)(temp & 0x00FF);
}

// AND - Logical AND
void nes_cpu::AND(uint16_t val)
{
    #ifdef CPU_DEBUG
        cout << "AND:" << endl;
    #endif

    #ifdef CPU_LOG
        cpuLogger.SetInstructionName("AND");
    #endif
    
    // AND accumulator and mem val
    a &= val;

    // Check Zero Flag
    (a == 0) ? (status |= Z_FLAG) : (status &= Z_FLAG_INV);

    // Check Negative Flag
    (a & 0x80) ? (status |= N_FLAG) : (status &= N_FLAG_INV);
}

// ASL - Arithmetic Shift Left
void nes_cpu::ASL(uint16_t address)
{
    #ifdef CPU_DEBUG
        cout << "ASL:" << endl;
    #endif

    #ifdef CPU_LOG
        cpuLogger.SetInstructionName("ASL");
    #endif

    uint8_t val = mem->read_8(address);

    // Check Carry Flag
    (val & 0x80) ? (status |= C_FLAG) : (status &= C_FLAG_INV);

    // Shift the memory value left one
    uint8_t temp = (val << 1);
    val = temp & 0xFE;

    // Check Zero Flag
    (temp == 0) ? (status |= Z_FLAG) : (status &= Z_FLAG_INV);

    // Check Negative Flag
    (temp & 0x80) ? (status |= N_FLAG) : (status &= N_FLAG_INV);

    mem->write_8(address, val);
}

void nes_cpu::ASL_ACC(uint16_t address)
{
    #ifdef CPU_DEBUG
        cout << "ASL:" << endl;
    #endif

    #ifdef CPU_LOG
        cpuLogger.SetInstructionName("ASL");
        cpuLogger.SetAddressingMode_8(0,0,0,3);
    #endif

    uint8_t val = a;

    // Check Carry Flag
    (val & 0x80) ? (status |= C_FLAG) : (status &= C_FLAG_INV);

    // Shift the memory value left one
    uint8_t temp = (val << 1);
    val = temp & 0xFE;

    // Check Zero Flag
    (temp == 0) ? (status |= Z_FLAG) : (status &= Z_FLAG_INV);

    // Check Negative Flag
    (temp & 0x80) ? (status |= N_FLAG) : (status &= N_FLAG_INV);

    a = val;
}

// BCC - Branch if Carry Clear
void nes_cpu::BCC(uint16_t offset)
{
    #ifdef CPU_DEBUG
        cout << "BCC:" << endl;
    #endif

    #ifdef CPU_LOG
        cpuLogger.SetInstructionName("BCC");
    #endif

    // Check if Carry Bit is Clear
    if (!(status & C_FLAG))
    {
        // If its a positive integer add to PC, If its a negative integer subtract to PC
        (offset & 0x80) ? (pc -= (((uint8_t)255 - offset) + 1)) : (pc += offset);
    }
}

// BCS - Branch if Carry Set
void nes_cpu::BCS(uint16_t offset)
{
    #ifdef CPU_DEBUG
        cout << "BCS:" << endl;
    #endif

    #ifdef CPU_LOG
        cpuLogger.SetInstructionName("BCS");
    #endif

    // Check if Carry Bit is Set
    if (status & C_FLAG)
    {
        // If its a positive integer add to PC, If its a negative integer subtract to PC
        (offset & 0x80) ? (pc -= (((uint8_t)255 - offset) + 1)) : (pc += offset);
    }
}

// BEQ - Branch if Equal
void nes_cpu::BEQ(uint16_t offset)
{
    #ifdef CPU_DEBUG
        cout << "BEQ:" << endl;
    #endif

    #ifdef CPU_LOG
        cpuLogger.SetInstructionName("BEQ");
    #endif

    // Check if Zero Flag is Set
    if (status & Z_FLAG)
    {
        // If its a positive integer add to PC, If its a negative integer subtract to PC
        (offset & 0x80) ? (pc -= (((uint8_t)255 - offset) + 1)) : (pc += offset);
    }
}

// BIT - Bit Test
void nes_cpu::BIT(uint16_t val)
{
    #ifdef CPU_DEBUG
        cout << "BIT:" << endl;
    #endif

    #ifdef CPU_LOG
        cpuLogger.SetInstructionName("BIT");
    #endif

    // Instruction doesnt affect any register value
    uint8_t temp = a & val;

    // Check Zero Flag
    (temp == 0) ? (status |= Z_FLAG) : (status &= Z_FLAG_INV);

    // Check Negative Flag
    (val & 0x80) ? (status |= N_FLAG) : (status &= N_FLAG_INV);

    // Check Overflow Flag
    (val & 0x40) ? (status |= V_FLAG) : (status &= V_FLAG_INV);
}

// BMI - Branch if Minus
void nes_cpu::BMI(uint16_t offset)
{
    #ifdef CPU_DEBUG
        cout << "BMI:" << endl;
    #endif

    #ifdef CPU_LOG
        cpuLogger.SetInstructionName("BMI");
    #endif

    // Check if Negative Flag is Set
    if (status & N_FLAG)
    {
        // If its a positive integer add to PC, If its a negative integer subtract to PC
        (offset & 0x80) ? (pc -= (((uint8_t)255 - offset) + 1)) : (pc += offset);
    }
}

// BNE - Branch if Not Equal
void nes_cpu::BNE(uint16_t offset)
{
    #ifdef CPU_DEBUG
        cout << "BNE:" << endl;
    #endif

    #ifdef CPU_LOG
        cpuLogger.SetInstructionName("BNE");
    #endif

    // Check if Zero Flag is Clear
    if (!(status & Z_FLAG))
    {
        // If its a positive integer add to PC, If its a negative integer subtract to PC
        (offset & 0x80) ? (pc -= (((uint8_t)255 - offset) + 1)) : (pc += offset);
    }
}

// BPL - Branch if Positive
void nes_cpu::BPL(uint16_t offset)
{
    #ifdef CPU_DEBUG
        cout << "BPL:" << endl;
    #endif

    #ifdef CPU_LOG
        cpuLogger.SetInstructionName("BPL");
    #endif

    // Check if Negative Flag is Clear
    if (!(status & N_FLAG))
    {
        // If its a positive integer add to PC, If its a negative integer subtract to PC
        (offset & 0x80) ? (pc -= (((uint8_t)255 - offset) + 1)) : (pc += offset);
    }
}

// BRK - Force Interrupt
void nes_cpu::BRK(uint16_t val)
{
    #ifdef CPU_DEBUG
        cout << "BRK:" << endl;
    #endif

    #ifdef CPU_LOG
        cpuLogger.SetInstructionName("BRK");
    #endif
    // Push PC to Stack
    // 6502 has error where is pushes PC + 1 instead of current PC, problem has to be fixed through software
    pc += 1;
    // Push High Byte
    mem->push(sp--, (uint8_t)((pc >> 8) & 0xFF));
    // Push Low Byte
    mem->push(sp--, (uint8_t)(pc & 0xFF));

    // Push Status with break flag set
    mem->push(sp--, status | B_FLAG);

    // Set PC to value in Interrupt Handler
    pc = mem->read_16(0xFFFE);
}

// BVC - Branch if Overflow Clear
void nes_cpu::BVC(uint16_t offset)
{
    #ifdef CPU_DEBUG
        cout << "BVC:" << endl;
    #endif

    #ifdef CPU_LOG
        cpuLogger.SetInstructionName("BVC");
    #endif

    // Check if Overflow Flag is Clear
    if (!(status & V_FLAG))
    {
        // If its a positive integer add to PC, If its a negative integer subtract to PC
        (offset & 0x80) ? (pc -= (((uint8_t)255 - offset) + 1)) : (pc += offset);
    }
}

// BVS - Branch if Overflow Set
void nes_cpu::BVS(uint16_t offset)
{
    #ifdef CPU_DEBUG
        cout << "BVS:" << endl;
    #endif

    #ifdef CPU_LOG
        cpuLogger.SetInstructionName("BVS");
    #endif

    // Check if Overflow Flag is Clear
    if (status & V_FLAG)
    {
        // If its a positive integer add to PC, If its a negative integer subtract to PC
        (offset & 0x80) ? (pc -= (((uint8_t)255 - offset) + 1)) : (pc += offset);
    }
}

// CLC - Clear Carry Flag
void nes_cpu::CLC(uint16_t val)
{
    #ifdef CPU_DEBUG
        cout << "CLC:" << endl;
    #endif

    #ifdef CPU_LOG
        cpuLogger.SetInstructionName("CLC");
    #endif

    status &= C_FLAG_INV;
}

// CLD - Clear Decimal Mode
void nes_cpu::CLD(uint16_t val)
{
    #ifdef CPU_DEBUG
        cout << "CLD:" << endl;
    #endif

    #ifdef CPU_LOG
        cpuLogger.SetInstructionName("CLD");
    #endif
    
    status &= D_FLAG_INV;
}

// CLI - Clear Interrupt Disable
void nes_cpu::CLI(uint16_t val)
{
    #ifdef CPU_DEBUG
        cout << "CLI:" << endl;
    #endif

    #ifdef CPU_LOG
        cpuLogger.SetInstructionName("CLI");
    #endif
    
    status &= I_FLAG_INV;
}

// CLV - Clear Overflow Flag
void nes_cpu::CLV(uint16_t val)
{
    #ifdef CPU_DEBUG
        cout << "CLV:" << endl;
    #endif
    

    #ifdef CPU_LOG
        cpuLogger.SetInstructionName("CLV");
    #endif
    status &= V_FLAG_INV;
}

// CMP - Compare
void nes_cpu::CMP(uint16_t val)
{
    #ifdef CPU_DEBUG
        cout << "CMP:" << endl;
    #endif

    #ifdef CPU_LOG
        cpuLogger.SetInstructionName("CMP");
    #endif
    
    // Subtract mem val from accumulator
    uint8_t temp = a - val;

    // Check the Carry Flag
    (a >= val) ? (status |= C_FLAG) : (status &= C_FLAG_INV);

    // Check the Zero Flag
    (temp == 0) ? (status |= Z_FLAG) : (status &= Z_FLAG_INV);

    // Check Negative Flag
    (temp & 0x80) ? (status |= N_FLAG) : (status &= N_FLAG_INV);
}

// CPX - Compare X Register
void nes_cpu::CPX(uint16_t val)
{
    #ifdef CPU_DEBUG
        cout << "CPX:" << endl;
    #endif

    #ifdef CPU_LOG
        cpuLogger.SetInstructionName("CPX");
    #endif
    
    // Subtract mem val from x
    uint8_t temp = x - val;

    // Check the Carry Flag
    (x >= val) ? (status |= C_FLAG) : (status &= C_FLAG_INV);

    // Check the Zero Flag
    (temp == 0) ? (status |= Z_FLAG) : (status &= Z_FLAG_INV);

    // Check Negative Flag
    (temp & 0x80) ? (status |= N_FLAG) : (status &= N_FLAG_INV);
}

// CPY - Compare Y Register
void nes_cpu::CPY(uint16_t val)
{
    #ifdef CPU_DEBUG
        cout << "CPY:" << endl;
    #endif

    #ifdef CPU_LOG
        cpuLogger.SetInstructionName("CPY");
    #endif
    
    // Subtract mem val from y
    uint8_t temp = y - val;

    // Check the Carry Flag
    (y >= val) ? (status |= C_FLAG) : (status &= C_FLAG_INV);

    // Check the Zero Flag
    (temp == 0) ? (status |= Z_FLAG) : (status &= Z_FLAG_INV);

    // Check Negative Flag
    (temp & 0x80) ? (status |= N_FLAG) : (status &= N_FLAG_INV);
}

// DEC - Decrement Memory
void nes_cpu::DEC(uint16_t address)
{
    #ifdef CPU_DEBUG
        cout << "DEC:" << endl;
    #endif

    #ifdef CPU_LOG
        cpuLogger.SetInstructionName("DEC");
    #endif
    
    // Decrement the Memory Value by One
    uint8_t val = mem->read_8(address);
    val -= 1;
    val &= 0xFF;

    // Check Zero Flag
    (val == 0) ? (status |= Z_FLAG) : (status &= Z_FLAG_INV);

    // Check Negative Flag
    (val & 0x80) ? (status |= N_FLAG) : (status &= N_FLAG_INV);

    mem->write_8(address, val);
}

// DEX - Decrement X Register
void nes_cpu::DEX(uint16_t val)
{
    #ifdef CPU_DEBUG
        cout << "DEX:" << endl;
    #endif

    #ifdef CPU_LOG
        cpuLogger.SetInstructionName("DEX");
    #endif
    
    // Decrement X by One
    x -= 1;

    // Check Zero Flag
    (x == 0) ? (status |= Z_FLAG) : (status &= Z_FLAG_INV);

    // Check Negative Flag
    (x & 0x80) ? (status |= N_FLAG) : (status &= N_FLAG_INV);
}

// DEY - Decrement Y Register
void nes_cpu::DEY(uint16_t val)
{
    #ifdef CPU_DEBUG
        cout << "DEY:" << endl;
    #endif

    #ifdef CPU_LOG
        cpuLogger.SetInstructionName("DEY");
    #endif
    
    // Decrement X by One
    y -= 1;

    // Check Zero Flag
    (y == 0) ? (status |= Z_FLAG) : (status &= Z_FLAG_INV);

    // Check Negative Flag
    (y & 0x80) ? (status |= N_FLAG) : (status &= N_FLAG_INV);
}

// EOR - Exclusive OR
void nes_cpu::EOR(uint16_t val)
{
    #ifdef CPU_DEBUG
        cout << "EOR:" << endl;
    #endif

    #ifdef CPU_LOG
        cpuLogger.SetInstructionName("EOR");
    #endif
    
    // Perform XOR on Accumulator
    a ^= val;

    // Check Zero Flag
    (a == 0) ? (status |= Z_FLAG) : (status &= Z_FLAG_INV);

    // Check Negative Flag
    (a & 0x80) ? (status |= N_FLAG) : (status &= N_FLAG_INV);
}

// INC - Increment Memory
void nes_cpu::INC(uint16_t address)
{
    #ifdef CPU_DEBUG
        cout << "INC:" << endl;
    #endif

    #ifdef CPU_LOG
        cpuLogger.SetInstructionName("INC");
    #endif
    
    uint8_t val = mem->read_8(address);

    // Increment the Memory Value by One
    val += 1;
    val &= 0xFF;

    // Check Zero Flag
    (val == 0) ? (status |= Z_FLAG) : (status &= Z_FLAG_INV);

    // Check Negative Flag
    (val & 0x80) ? (status |= N_FLAG) : (status &= N_FLAG_INV);

    mem->write_8(address, val);
}

// INX - Increment X Register
void nes_cpu::INX(uint16_t val)
{
    #ifdef CPU_DEBUG
        cout << "INX:" << endl;
    #endif

    #ifdef CPU_LOG
        cpuLogger.SetInstructionName("INX");
    #endif
    
    // Increment X by One
    x += 1;

    // Check Zero Flag
    (x == 0) ? (status |= Z_FLAG) : (status &= Z_FLAG_INV);

    // Check Negative Flag
    (x & 0x80) ? (status |= N_FLAG) : (status &= N_FLAG_INV);
}

// INY - Increment Y Register
void nes_cpu::INY(uint16_t val)
{
    #ifdef CPU_DEBUG
        cout << "INY:" << endl;
    #endif

    #ifdef CPU_LOG
        cpuLogger.SetInstructionName("INY");
    #endif
    
    // Increment Y by One
    y += 1;

    // Check Zero Flag
    (y == 0) ? (status |= Z_FLAG) : (status &= Z_FLAG_INV);

    // Check Negative Flag
    (y & 0x80) ? (status |= N_FLAG) : (status &= N_FLAG_INV);
}

// JMP - Jump
void nes_cpu::JMP(uint16_t address)
{
    #ifdef CPU_DEBUG
        cout << "JMP:" << endl;
    #endif

    #ifdef CPU_LOG
        cpuLogger.SetInstructionName("JMP");
    #endif
    
    // Set PC to address
    pc = address;
}

// JSR - Jump to Subroutine
void nes_cpu::JSR(uint16_t address)
{
    #ifdef CPU_DEBUG
        cout << "JSR:" << endl;
    #endif

    #ifdef CPU_LOG
        cpuLogger.SetInstructionName("JSR");
    #endif
    
    // Pushes (address - 1) of return point on to the stack
    pc -= 1;
    uint8_t HI = (uint8_t)((pc >> 8) & 0xFF);
    uint8_t LO = (uint8_t)(pc & 0xFF);
    mem->push(sp--, HI);
    mem->push(sp--, LO);

    // Sets PC to Target Memory Address
    pc = address;
}

// LDA - Load Accumulator
void nes_cpu::LDA(uint16_t val)
{
    #ifdef CPU_DEBUG
        cout << "LDA:" << endl;
    #endif

    #ifdef CPU_LOG
        cpuLogger.SetInstructionName("LDA");
    #endif
    
    // Set Accumulator to Memory Value
    a = val;
    
    // Check Zero Flag
    (a == 0) ? (status |= Z_FLAG) : (status &= Z_FLAG_INV);

    // Check Negative Flag
    (a & 0x80) ? (status |= N_FLAG) : (status &= N_FLAG_INV);
}

// LDX - Load X Register
void nes_cpu::LDX(uint16_t val)
{
    #ifdef CPU_DEBUG
        cout << "LDX:" << endl;
    #endif

    #ifdef CPU_LOG
        cpuLogger.SetInstructionName("LDX");
    #endif
    
    // Set X to Memory Value
    x = val;

    // Check Zero Flag
    (x == 0) ? (status |= Z_FLAG) : (status &= Z_FLAG_INV);

    // Check Negative Flag
    (x & 0x80) ? (status |= N_FLAG) : (status &= N_FLAG_INV);
}

// LDY - Load Y Register
void nes_cpu::LDY(uint16_t val)
{
    #ifdef CPU_DEBUG
        cout << "LDY:" << endl;
    #endif

    #ifdef CPU_LOG
        cpuLogger.SetInstructionName("LDY");
    #endif
    
    // Set Y to Memory Value
    y = val;

    // Check Zero Flag
    (y == 0) ? (status |= Z_FLAG) : (status &= Z_FLAG_INV);

    // Check Negative Flag
    (y & 0x80) ? (status |= N_FLAG) : (status &= N_FLAG_INV);
}

// LSR - Logical Shift Right
void nes_cpu::LSR(uint16_t address)
{
    #ifdef CPU_DEBUG
        cout << "LSR:" << endl;
    #endif

    #ifdef CPU_LOG
        cpuLogger.SetInstructionName("LSR");
    #endif
    
    uint8_t val = mem->read_8(address);

    // Check Carry Flag
    (val & 0x01) ? (status |= C_FLAG) : (status &= C_FLAG_INV);

    // Shift the memory value left one
    uint8_t temp = (val >> 1);
    val = temp;

    // Check Zero Flag
    (temp == 0) ? (status |= Z_FLAG) : (status &= Z_FLAG_INV);

    // Clear Negative Flag (leftmost bit always 0)
    status &= N_FLAG_INV;

    mem->write_8(address, val);
}
void nes_cpu::LSR_ACC(uint16_t address)
{
    #ifdef CPU_DEBUG
        cout << "LSR:" << endl;
    #endif

    #ifdef CPU_LOG
        cpuLogger.SetInstructionName("LSR");
        cpuLogger.SetAddressingMode_8(0,0,0,3);
    #endif
    
    uint8_t val = a;

    // Check Carry Flag
    (val & 0x01) ? (status |= C_FLAG) : (status &= C_FLAG_INV);

    // Shift the memory value left one
    uint8_t temp = (val >> 1);
    val = temp;

    // Check Zero Flag
    (temp == 0) ? (status |= Z_FLAG) : (status &= Z_FLAG_INV);

    // Clear Negative Flag (leftmost bit always 0)
    status &= N_FLAG_INV;

    a = val;
}

// NOP - No Operation
void nes_cpu::NOP(uint16_t val) {
    #ifdef CPU_DEBUG
        cout << "NOP:" << endl;
    #endif

    #ifdef CPU_LOG
        cpuLogger.SetInstructionName("NOP");
    #endif
}

// ORA - Logical Inclusive OR
void nes_cpu::ORA(uint16_t val)
{
    #ifdef CPU_DEBUG
        cout << "ORA:" << endl;
    #endif

    #ifdef CPU_LOG
        cpuLogger.SetInstructionName("ORA");
    #endif
    
    // Inclusive OR Performed on Accumulator and Memory Value
    a |= val;

    // Check Zero Flag
    (a == 0) ? (status |= Z_FLAG) : (status &= Z_FLAG_INV);

    // Check Negative Flag
    (a & 0x80) ? (status |= N_FLAG) : (status &= N_FLAG_INV);
}

// PHA - Push Accumulator
void nes_cpu::PHA(uint16_t val)
{
    #ifdef CPU_DEBUG
        cout << "PHA:" << endl;
    #endif

    #ifdef CPU_LOG
        cpuLogger.SetInstructionName("PHA");
    #endif
    
    mem->push(sp, a);
    sp -= 1;
}

// PHP - Push Processor Status
void nes_cpu::PHP(uint16_t val)
{
    #ifdef CPU_DEBUG
        cout << "PHP:" << endl;
    #endif

    #ifdef CPU_LOG
        cpuLogger.SetInstructionName("PHP");
    #endif
    
    mem->push(sp--, status | B_FLAG);
}

// PLA - Pull Accumulator
void nes_cpu::PLA(uint16_t val)
{
    #ifdef CPU_DEBUG
        cout << "PLA:" << endl;
    #endif

    #ifdef CPU_LOG
        cpuLogger.SetInstructionName("PLA");
    #endif
    
    sp += 1;
    a = mem->pop(sp);

    // Check Zero Flag
    (a == 0) ? (status |= Z_FLAG) : (status &= Z_FLAG_INV);

    // Check Negative Flag
    (a & 0x80) ? (status |= N_FLAG) : (status &= N_FLAG_INV);
}

// PLP - Pull Processor Status (Break Flag and Bit 5 Ignored)
void nes_cpu::PLP(uint16_t val)
{
    #ifdef CPU_DEBUG
        cout << "PLP:" << endl;
    #endif

    #ifdef CPU_LOG
        cpuLogger.SetInstructionName("PLP");
    #endif
    
    sp += 1;
    status = mem->pop(sp);
    status &= B_FLAG_INV;
    status |= 0b00100000;
}

// ROL - Rotate Left
void nes_cpu::ROL(uint16_t address)
{
    #ifdef CPU_DEBUG
        cout << "ROL:" << endl;
    #endif

    #ifdef CPU_LOG
        cpuLogger.SetInstructionName("ROL");
    #endif
    
    uint8_t val = mem->read_8(address);

    // Move Memory Value one to Left
    uint8_t temp = (val << 1);

    // Bit 0 - filled with current Carry Flag Value
    temp |= (status & C_FLAG);

    // Bit 7 becomes new Carry Flag Value
    (val & 0x80) ? (status |= C_FLAG) : (status &= C_FLAG_INV);

    // Set Memory to new Value
    mem->write_8(address, temp);

    // Check Zero Flag
    (temp == 0) ? (status |= Z_FLAG) : (status &= Z_FLAG_INV);

    // Check Negative Flag
    (temp & 0x80) ? (status |= N_FLAG) : (status &= N_FLAG_INV);
}
void nes_cpu::ROL_ACC(uint16_t address)
{
    #ifdef CPU_DEBUG
        cout << "ROL:" << endl;
    #endif

    #ifdef CPU_LOG
        cpuLogger.SetInstructionName("ROL");
        cpuLogger.SetAddressingMode_8(0,0,0,3);
    #endif
    
    // Move Accumulator Value one to Left
    uint8_t temp = (a << 1);

    // Bit 0 - filled with current Carry Flag Value
    temp |= (status & C_FLAG);

    // Bit 7 becomes new Carry Flag Value
    (a & 0x80) ? (status |= C_FLAG) : (status &= C_FLAG_INV);

    // Set Memory to new Value
    a = temp;

    // Check Zero Flag
    (temp == 0) ? (status |= Z_FLAG) : (status &= Z_FLAG_INV);

    // Check Negative Flag
    (temp & 0x80) ? (status |= N_FLAG) : (status &= N_FLAG_INV);
}

// ROR - Rotate Right
void nes_cpu::ROR(uint16_t address)
{
    #ifdef CPU_DEBUG
        cout << "ROR:" << endl;
    #endif

    #ifdef CPU_LOG
        cpuLogger.SetInstructionName("ROR");
    #endif

    uint8_t val = mem->read_8(address);

    // Move Memory Value one to Right
    uint8_t temp = (val >> 1);

    // Bit 7 - filled with current Carry Flag Value
    temp |= ((status & C_FLAG) << 7);

    // Bit 0 becomes new Carry Flag Value
    (val & 0x01) ? (status |= C_FLAG) : (status &= C_FLAG_INV);

    // Set Memory to new Value
    mem->write_8(address, temp);

    // Check Zero Flag
    (temp == 0) ? (status |= Z_FLAG) : (status &= Z_FLAG_INV);

    // Check Negative Flag
    (temp & 0x80) ? (status |= N_FLAG) : (status &= N_FLAG_INV);
}
void nes_cpu::ROR_ACC(uint16_t address)
{
    #ifdef CPU_DEBUG
        cout << "ROR:" << endl;
    #endif

    #ifdef CPU_LOG
        cpuLogger.SetInstructionName("ROR");
        cpuLogger.SetAddressingMode_8(0,0,0,3);
    #endif
    
    // Move Memory Value one to Right
    uint8_t temp = (a >> 1);

    // Bit 7 - filled with current Carry Flag Value
    temp |= ((status & C_FLAG) << 7);

    // Bit 0 becomes new Carry Flag Value
    (a & 0x01) ? (status |= C_FLAG) : (status &= C_FLAG_INV);

    // Set Memory to new Value
    a = temp;

    // Check Zero Flag
    (temp == 0) ? (status |= Z_FLAG) : (status &= Z_FLAG_INV);

    // Check Negative Flag
    (temp & 0x80) ? (status |= N_FLAG) : (status &= N_FLAG_INV);
}

// RTI - Return from Interrupt
void nes_cpu::RTI(uint16_t val)
{
    #ifdef CPU_DEBUG
        cout << "RTI:" << endl;
    #endif

    #ifdef CPU_LOG
        cpuLogger.SetInstructionName("RTI");
    #endif
    
    // Pull Status from Stack
    sp += 1;
    status = mem->pop(sp);
    status |= 0b00100000;

    // Pull Low Byte of PC from Stack
    sp += 1;
    pc |= mem->pop(sp);

    // Pull High Byte of PC from Stack
    sp += 1;
    pc |= (uint16_t)(mem->pop(sp) << 8);
}

// RTS - Return from Subroutine
void nes_cpu::RTS(uint16_t val)
{
    #ifdef CPU_DEBUG
        cout << "RTS:" << endl;
    #endif

    #ifdef CPU_LOG
        cpuLogger.SetInstructionName("RTS");
    #endif
    
    // Pull Low Byte of PC from Stack
    sp += 1;
    uint16_t temp = mem->pop(sp);

    // Pull High Byte of PC from Stack
    sp += 1;
    temp |= (uint16_t)(mem->pop(sp) << 8);

    // Increment PC by 1
    pc = temp;
    pc += 1;
}

// SBC - Subtract with Carry
void nes_cpu::SBC(uint16_t val)
{
    #ifdef CPU_DEBUG
        cout << "SBC:" << endl;
    #endif


    #ifdef CPU_LOG
        cpuLogger.SetInstructionName("SBC");
    #endif
    // Subtract val and Not of Carry from Accumulator
    int8_t temp = a - (uint8_t)val - ((uint8_t)1 - (status & C_FLAG));

    // Check Carry Flag
    (temp >= 0) ? (status |= C_FLAG) : (status &= C_FLAG_INV);

    // Check Overflow Flag | Formula for Calculating the Overflow Flag Taken from https://www.righto.com/2012/12/the-6502-overflow-flag-explained.html
    ((a^val) & ((uint8_t)(temp & 0x00FF)^a) & 0x80) ? (status |= V_FLAG) : (status &= V_FLAG_INV);

    // Check Zero Flag
    ((uint8_t)(temp & 0x00FF) == 0) ? (status |= Z_FLAG) : (status &= Z_FLAG_INV);

    // Check Negative Flag
    ((uint8_t)(temp & 0x0080)) ? (status |= N_FLAG) : (status &= N_FLAG_INV);

    // Set Accumulator to new value
    a = (uint8_t)(temp & 0xFF);
}

// SEC - Set Carry Flag
void nes_cpu::SEC(uint16_t val)
{
    #ifdef CPU_DEBUG
        cout << "SEC:" << endl;
    #endif

    #ifdef CPU_LOG
        cpuLogger.SetInstructionName("SEC");
    #endif
    
    status |= C_FLAG;
}

// SED - Set Decimal Flag
void nes_cpu::SED(uint16_t val)
{
    #ifdef CPU_DEBUG
        cout << "SED:" << endl;
    #endif

    #ifdef CPU_LOG
        cpuLogger.SetInstructionName("SED");
    #endif
    
    status |= D_FLAG;
}

// SEI - Set Interrupt Disable
void nes_cpu::SEI(uint16_t val)
{
    #ifdef CPU_DEBUG
        cout << "SEI:" << endl;
    #endif

    #ifdef CPU_LOG
        cpuLogger.SetInstructionName("SEI");
    #endif
    
    status |= I_FLAG;
}

// STA - Store Accumulator
void nes_cpu::STA(uint16_t address)
{
    #ifdef CPU_DEBUG
        cout << "STA:" << endl;
    #endif

    #ifdef CPU_LOG
        cpuLogger.SetInstructionName("STA");
    #endif
    
    mem->write_8(address, a);
}

// STX - Store X
void nes_cpu::STX(uint16_t address)
{
    #ifdef CPU_DEBUG
        cout << "STX:" << endl;
    #endif

    #ifdef CPU_LOG
        cpuLogger.SetInstructionName("STX");
    #endif
    
    mem->write_8(address, x);
}

// // STY - Store Y
void nes_cpu::STY(uint16_t address)
{
    #ifdef CPU_DEBUG
        cout << "STY:" << endl;
    #endif

    #ifdef CPU_LOG
        cpuLogger.SetInstructionName("STY");
    #endif
    
    mem->write_8(address, y);
}

// TAX - Transfer Accumulator to X
void nes_cpu::TAX(uint16_t val)
{
    #ifdef CPU_DEBUG
        cout << "TAX:" << endl;
    #endif

    #ifdef CPU_LOG
        cpuLogger.SetInstructionName("TAX");
    #endif
    
    x = a;

    // Check Zero Flag
    (x == 0) ? (status |= Z_FLAG) : (status &= Z_FLAG_INV);

    // Check Negative Flag
    (x & 0x80) ? (status |= N_FLAG) : (status &= N_FLAG_INV);
}

// TAY - Transfer Accumulator to Y
void nes_cpu::TAY(uint16_t val)
{
    #ifdef CPU_DEBUG
        cout << "TAY:" << endl;
    #endif

    #ifdef CPU_LOG
        cpuLogger.SetInstructionName("TAY");
    #endif
    
    y = a;

    // Check Zero Flag
    (y == 0) ? (status |= Z_FLAG) : (status &= Z_FLAG_INV);

    // Check Negative Flag
    (y & 0x80) ? (status |= N_FLAG) : (status &= N_FLAG_INV);
}

// TSX - Transfer Stack Pointer to X
void nes_cpu::TSX(uint16_t val)
{
    #ifdef CPU_DEBUG
        cout << "TSX:" << endl;
    #endif

    #ifdef CPU_LOG
        cpuLogger.SetInstructionName("TSX");
    #endif
    
    x = sp;

    // Check Zero Flag
    (x == 0) ? (status |= Z_FLAG) : (status &= Z_FLAG_INV);

    // Check Negative Flag
    (x & 0x80) ? (status |= N_FLAG) : (status &= N_FLAG_INV);
}

// TXA - Transfer X to Accumulator
void nes_cpu::TXA(uint16_t val)
{
    #ifdef CPU_DEBUG
        cout << "TXA:" << endl;
    #endif

    #ifdef CPU_LOG
        cpuLogger.SetInstructionName("TXA");
    #endif
    
    a = x;

    // Check Zero Flag
    (a == 0) ? (status |= Z_FLAG) : (status &= Z_FLAG_INV);

    // Check Negative Flag
    (a & 0x80) ? (status |= N_FLAG) : (status &= N_FLAG_INV);
}

// TXS - Transfer X to Stack Pointer
void nes_cpu::TXS(uint16_t val)
{
    #ifdef CPU_DEBUG
        cout << "TXS:" << endl;
    #endif

    #ifdef CPU_LOG
        cpuLogger.SetInstructionName("TXS");
    #endif
    
    sp = x;
}

// TYA - Transfer Y to Accumulator
void nes_cpu::TYA(uint16_t val)
{
    #ifdef CPU_DEBUG
        cout << "TYA:" << endl;
    #endif

    #ifdef CPU_LOG
        cpuLogger.SetInstructionName("TYA");
    #endif
    
    a = y;

    // Check Zero Flag
    (a == 0) ? (status |= Z_FLAG) : (status &= Z_FLAG_INV);

    // Check Negative Flag
    (a & 0x80) ? (status |= N_FLAG) : (status &= N_FLAG_INV);
}