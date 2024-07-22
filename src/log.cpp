#include "../inc/log.h"

using namespace std;

void byte2hex(uint8_t input, char *output);
void word2hex(uint16_t input, char *output);

Logger::Logger(){
    // Remove Old Log File
    remove("./logs/log.log");

    // Set the Log String to White Space
    for(int i = 0; i < 100; i++){
        log[i] = ' ';
    }


    // Format Log String
    log[48] = 'A';
    log[49] = ':';

    log[53] = 'X';
    log[54] = ':';

    log[58] = 'Y';
    log[59] = ':';

    log[63] = 'P';
    log[64] = ':';

    log[68] = 'S';
    log[69] = 'P';
    log[70] = ':';

    log[99] = '\n';
}

Logger::~Logger(){}

void Logger::Log(){
    if(!ofstream("./logs/log.log", ios::app | ios::binary | ios::out).write(log, 100)){
        cout << "Failed to Write to Log File" << endl;
    }
    
    for(int i = 0; i < 8; i++){
        log[20 + i] = ' ';
    }
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

    log[9] = ' ';
    log[10] = ' ';
    log[12] = ' ';
    log[13] = ' ';
}

void Logger::SetAcc(uint8_t data){
    // Put Char Representation of PC into an array
    char temp[2];
    byte2hex(data, temp);

    // Copy Array to log array
    log[50] = temp[0];
    log[51] = temp[1];
}

void Logger::SetX(uint8_t data){
    // Put Char Representation of PC into an array
    char temp[2];
    byte2hex(data, temp);

    // Copy Array to log array
    log[55] = temp[0];
    log[56] = temp[1];
}

void Logger::SetY(uint8_t data){
    // Put Char Representation of PC into an array
    char temp[2];
    byte2hex(data, temp);

    // Copy Array to log array
    log[60] = temp[0];
    log[61] = temp[1];
}

void Logger::SetStatus(uint8_t data){
    // Put Char Representation of PC into an array
    char temp[2];
    byte2hex(data, temp);

    // Copy Array to log array
    log[65] = temp[0];
    log[66] = temp[1];
}

void Logger::SetStackPointer(uint8_t data){
    // Put Char Representation of PC into an array
    char temp[2];
    byte2hex(data, temp);

    // Copy Array to log array
    log[71] = temp[0];
    log[72] = temp[1];
}

void Logger::SetAddressingMode_8(uint8_t data, uint16_t mem, uint8_t mode){

    // Put Char Representation of PC into an array
    char dataTemp[2];
    byte2hex(data, dataTemp);

    char memTemp[4];
    // Copy Array to log array
    log[9] = dataTemp[0];
    log[10] = dataTemp[1];

    switch(mode){
        // Imm
        case 0:
            log[20] = '#';
            log[21] = '$';
            log[22] = dataTemp[0];
            log[23] = dataTemp[1];
            break;
        // ZPG
        // ZPX
        // ZPY
        case 1:
            byte2hex(mem, memTemp);
            log[20] = '$';
            log[21] = dataTemp[0];
            log[22] = dataTemp[1];
            log[24] = '=';
            log[26] = memTemp[0];
            log[27] = memTemp[1];
            break;
        // REL
        case 2:
            (data & 0x80) ? (mem -= (((uint8_t)255 - data) + 1)) : (mem += data);
            word2hex(mem, memTemp);
            log[20] = '$';
            log[21] = memTemp[0];
            log[22] = memTemp[1];
            log[23] = memTemp[2];
            log[24] = memTemp[3];
            break;
        default:
            break;
    }
}

void Logger::SetAddressingMode_16(uint16_t data){    
    // Put Char Representation of PC into an array
    char temp[4];
    word2hex(data, temp);

    // Copy Array to log array
    log[9] = temp[2];
    log[10] = temp[3];
    log[12] = temp[0];
    log[13] = temp[1];

    log[20] = '$';
    log[21] = temp[0];
    log[22] = temp[1];
    log[23] = temp[2];
    log[24] = temp[3];
}

// Takes in a 3 character string with instructions name
void Logger::SetInstructionName(string name){
    log[16] = name[0];
    log[17] = name[1];
    log[18] = name[2];
}

char* Logger::GetLog(){
    return log;
}


//----------Helper Functions----------//

void byte2hex(uint8_t input, char *output)
{
    char HexLookUp[] = "0123456789ABCDEF";
    *output++ = HexLookUp[input >> 4];
    *output = HexLookUp[input & 0x0F];
}

void word2hex(uint16_t input, char *output)
{
    char HexLookUp[] = "0123456789ABCDEF";
    *output++ = HexLookUp[(input >> 12) & 0x0F];
    *output++ = HexLookUp[(input >> 8) & 0x0F];
    *output++ = HexLookUp[(input >> 4) & 0x0F];
    *output = HexLookUp[input & 0x0F];
}