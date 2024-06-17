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

void nes_cpu::evaluate(unsigned char opcode)
{
    if(debug == 1){
        cout << endl << "//----------CPU EVALUATE STARTING----------//" << endl;
        cout << "//-------------Before CPU State------------//" << endl;
        this->print_CPU_state();
    }

    //Actual Evaluate Code Goes Here
    switch(opcode){
    //ADC - Add With Carry
        case 0x69:
            //immediate
            break;
        case 0x65:
            //Zero Page
            break;
        case 0x75:
            //Zero Page X
            break;
        case 0x6D:
            //Absolute
            break;
        case 0x7D:
            //Absolute X
            break;
        case 0x79:
            //Abolute Y
            break;
        case 0x61:
            //Indirect X
            break;
        case 0x71:
            //Indirect Y
            break;
    //AND - Logical AND
        case 0x29:
            //Immidiate
            break;
        case 0x25:
            //Zero Page
            break;
        case 0x35:
            //Zero Page X
            break;
        case 0x2D:
            //Absolute
            break;
        case 0x3D:
            //Absolute X
            break;
        case 0x39:
            //Absolute Y
            break;
        case 0x21:
            //Indirect X
            break;
        case 0x31:
            //Indirect Y
            break;
    //ASL - Arithmetic Shift Left
        case 0x41:
            //



        default:
            break;
    }

    if(debug == 1){
        cout << "//-------------After CPU State-------------//" << endl;
        this->print_CPU_state();
    }

}

void nes_cpu::set_mem(nes_mem* _mem){
    mem = _mem;
}

void nes_cpu::set_debug(int val){
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
    //implied directly by the function of the instruction itself
void *nes_cpu::IMP(){
    return nullptr;
}
// Accumulator
    //operate directly upon the accumulator
void *nes_cpu::ACC(){
    return &this->a;
}

// Immediate
    //directly specify an 8 bit constant within the instruction 
void *nes_cpu::IMM(){
    return nullptr;
}
// Zero Page
void *nes_cpu::ZPG(){
    return nullptr;
}

// Zero Page X
void *nes_cpu::ZPX(){
    return nullptr;
}

// Zero Page Y
void *nes_cpu::ZPY(){
    return nullptr;
}

// Relative
void *nes_cpu::REL(){
    return nullptr;
}

// Absolute
void *nes_cpu::ABS(){
    return nullptr;
}

// Absolute X
void *nes_cpu::ABX(){
    return nullptr;
}

// Absolute Y
void *nes_cpu::ABY(){
    return nullptr;
}

// Indirect
void *nes_cpu::IND(){
    return nullptr;
}

// Indexed Indirect
void *nes_cpu::IID(){
    return nullptr;
}

// Indirect Indexed
void *nes_cpu::IDI(){
    return nullptr;
}

