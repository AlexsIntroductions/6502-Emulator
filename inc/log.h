#pragma once
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class Logger{
    /** Structure of curLog
     *  [0:3] - program counter
     *  [6:7] - opcode
     *  [9:10] - Low Byte of Addressing Mode
     *  [12:13] - High Byte of Addressing Mode
     *  [42:46] - Accumulator
     *  [48:52] - X register
     *  [54:58] - Y Register
     *  [60:64] - Status Register
     *  [66:70] - Stack Pointer
     *  [72:80] - PPU
     *  [82:90] - Cycle Counter
    */
    char log[100];
public:
    Logger();
    ~Logger();

    void Log();

    void SetPC(uint16_t data);
    void SetOpcode(uint8_t data);
    void SetAcc(uint8_t data);
    void SetX(uint8_t data);
    void SetY(uint8_t data);
    void SetStatus(uint8_t data);
    void SetStackPointer(uint8_t data);
    void SetAddressingMode_8(uint8_t data, uint8_t mem, uint8_t mode);
    void SetAddressingMode_16(uint16_t data);  

    void SetInstructionName(string name);

    char* GetLog();
};