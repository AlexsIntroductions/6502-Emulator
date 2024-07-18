#include "../inc/log.h"

using namespace std;

void byte2hex(uint8_t input, char *output);
void word2hex(uint16_t input, char *output);

Logger::Logger(){
    // Remove Old Log File
    remove("./logs/log.txt");

    // Set the Log String to White Space
    for(int i = 0; i < 100; i++){
        log[i] = ' ';
    }


    // Format Log String
    log[43] = 'A';
    log[44] = ':';

    log[48] = 'X';
    log[49] = ':';

    log[55] = 'Y';
    log[56] = ':';

    log[61] = 'P';
    log[62] = ':';

    log[66] = 'S';
    log[67] = 'P';
    log[68] = ':';

    log[99] = '\n';
}

Logger::~Logger(){}

void Logger::Log(){
    if(!ofstream("./logs/log.txt", ios::app | ios::binary | ios::out).write(log, 100)){
        cout << "Failed to Write to Log File" << endl;
    }
    log[9] = ' ';
    log[10] = ' ';
    log[12] = ' ';
    log[13] = ' ';
}

void Logger::SetPC(uint16_t data){
    // Put Char Representation of PC into an array
    char temp[4];
    word2hex(data, temp);

    // Copy Array to log array
    for(unsigned int i = 0; i < 4; i++){
        log[i] = temp[i];
    }
}

void Logger::SetOpcode(uint8_t data){
    // Put Char Representation of PC into an array
    char temp[2];
    byte2hex(data, temp);

    // Copy Array to log array
    log[6] = temp[0];
    log[7] = temp[1];
}

void Logger::SetAcc(uint8_t data){
    // Put Char Representation of PC into an array
    char temp[2];
    byte2hex(data, temp);

    // Copy Array to log array
    log[45] = temp[0];
    log[46] = temp[1];
}

void Logger::SetX(uint8_t data){
    // Put Char Representation of PC into an array
    char temp[2];
    byte2hex(data, temp);

    // Copy Array to log array
    log[51] = temp[0];
    log[52] = temp[1];
}

void Logger::SetY(uint8_t data){
    // Put Char Representation of PC into an array
    char temp[2];
    byte2hex(data, temp);

    // Copy Array to log array
    log[57] = temp[0];
    log[58] = temp[1];
}

void Logger::SetStatus(uint8_t data){
    // Put Char Representation of PC into an array
    char temp[2];
    byte2hex(data, temp);

    // Copy Array to log array
    log[63] = temp[0];
    log[64] = temp[1];
}

void Logger::SetStackPointer(uint8_t data){
    // Put Char Representation of PC into an array
    char temp[2];
    byte2hex(data, temp);

    // Copy Array to log array
    log[69] = temp[0];
    log[70] = temp[1];
}

void Logger::SetAddressingMode_8(uint8_t data){
    // Put Char Representation of PC into an array
    char temp[2];
    byte2hex(data, temp);

    // Copy Array to log array
    log[9] = temp[0];
    log[10] = temp[1];
}

void Logger::SetAddressingMode_16(uint16_t data){    // Put Char Representation of PC into an array
    char temp[4];
    word2hex(data, temp);

    // Copy Array to log array
    log[9] = temp[2];
    log[10] = temp[3];
    log[12] = temp[0];
    log[13] = temp[1];
}

char* Logger::GetLog(){
    return log;
}


//----------Helper Functions----------//

void byte2hex(uint8_t input, char *output)
{
    char HexLookUp[] = "0123456789abcdef";
    *output++ = HexLookUp[input >> 4];
    *output = HexLookUp[input & 0x0F];
}

void word2hex(uint16_t input, char *output)
{
    char HexLookUp[] = "0123456789abcdef";
    *output++ = HexLookUp[(input >> 12) & 0x0F];
    *output++ = HexLookUp[(input >> 8) & 0x0F];
    *output++ = HexLookUp[(input >> 4) & 0x0F];
    *output = HexLookUp[input & 0x0F];
}