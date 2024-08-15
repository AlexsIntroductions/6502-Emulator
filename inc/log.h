#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

class Logger{
    int logMode;
    char pc[4];
    char opcode[2];
    char acc[2];
    char x[2];
    char y[2];
    char status[2];
    char sp[2];
    char cycles[sizeof(int)*8+1];
    char log[100];
    int length;
public:
    Logger();
    Logger(int mode);
    ~Logger();

    void Log();
    void SetMode(int mode);

    void SetPC(uint16_t data);
    void SetOpcode(uint8_t data);
    void SetAcc(uint8_t data);
    void SetX(uint8_t data);
    void SetY(uint8_t data);
    void SetStatus(uint8_t data);
    void SetStackPointer(uint8_t data);
    void SetCycles(int data);
    void SetAddressingMode(uint16_t data, uint16_t mem, uint16_t additionals, uint8_t mode);
    void SetInstructionName(string name);

    void CompareNesTestLogs();
    void CompareNesTestv2Logs();

private:
    void SetMode0();
    void SetAddressingMode0(uint16_t data, uint16_t mem, uint16_t additionals, uint8_t mode);
    void SetMode1();
};