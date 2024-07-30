#include "../inc/log.h"

using namespace std;

bool compareCStr(const char *str1, const char *str2, size_t endIndex);
void byte2hex(uint8_t input, char *output);
void word2hex(uint16_t input, char *output);

Logger::Logger()
{
    // Remove Old Log File
    remove("./logs/log.log");

    // Set the Log String to White Space
    for (int i = 0; i < 100; i++)
    {
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

Logger::~Logger() {}

void Logger::Log()
{
    if (!ofstream("./logs/log.log", ios::app | ios::binary | ios::out).write(log, 100))
    {
        cout << "Failed to Write to Log File" << endl;
    }

    log[9] = ' ';
    log[10] = ' ';
    log[12] = ' ';
    log[13] = ' ';
    for (int i = 20; i < 47; i++)
    {
        log[i] = ' ';
    }
}

void Logger::SetPC(uint16_t data)
{
    // Put Char Representation of PC into an array
    char temp[4];
    word2hex(data, temp);

    // Copy Array to log array
    for (unsigned int i = 0; i < 4; i++)
    {
        log[i] = temp[i];
    }
}

void Logger::SetOpcode(uint8_t data)
{
    // Put Char Representation of PC into an array
    char temp[2];
    byte2hex(data, temp);

    // Copy Array to log array
    log[6] = temp[0];
    log[7] = temp[1];
}

void Logger::SetAcc(uint8_t data)
{
    // Put Char Representation of PC into an array
    char temp[2];
    byte2hex(data, temp);

    // Copy Array to log array
    log[50] = temp[0];
    log[51] = temp[1];
}

void Logger::SetX(uint8_t data)
{
    // Put Char Representation of PC into an array
    char temp[2];
    byte2hex(data, temp);

    // Copy Array to log array
    log[55] = temp[0];
    log[56] = temp[1];
}

void Logger::SetY(uint8_t data)
{
    // Put Char Representation of PC into an array
    char temp[2];
    byte2hex(data, temp);

    // Copy Array to log array
    log[60] = temp[0];
    log[61] = temp[1];
}

void Logger::SetStatus(uint8_t data)
{
    // Put Char Representation of PC into an array
    char temp[2];
    byte2hex(data, temp);

    // Copy Array to log array
    log[65] = temp[0];
    log[66] = temp[1];
}

void Logger::SetStackPointer(uint8_t data)
{
    // Put Char Representation of PC into an array
    char temp[2];
    byte2hex(data, temp);

    // Copy Array to log array
    log[71] = temp[0];
    log[72] = temp[1];
}

void Logger::SetAddressingMode_8(uint8_t data, uint16_t mem, uint8_t additionals,uint8_t mode)
{

    // Put Char Representation of PC into an array
    char dataTemp[2];
    byte2hex(data, dataTemp);

    char memTemp[4];
    char additionalsTemp[4];
    // Copy Array to log array
    if(mode != 3){
        log[9] = dataTemp[0];
        log[10] = dataTemp[1];
    }

    switch (mode)
    {
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
        byte2hex((uint8_t)mem & 0xFF, memTemp);
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
    // ACC
    case 3:
        log[20] = 'A';
        break;
    // ZPX
    case 4:
        word2hex(mem, memTemp);
        byte2hex(additionals, additionalsTemp);
        log[9] = dataTemp[0];
        log[10] = dataTemp[1];
        log[12] = ' ';
        log[13] = ' ';
        
        log[20] = '$';
        log[21] = dataTemp[0];
        log[22] = dataTemp[1];
        log[23] = ',';
        log[24] = 'X';
        log[26] = '@';
        log[28] = additionalsTemp[0];
        log[29] = additionalsTemp[1];
        log[31] = '=';
        log[33] = memTemp[2];
        log[34] = memTemp[3];
        break;
    // ZPY
    case 5:
        word2hex(mem, memTemp);
        byte2hex(additionals, additionalsTemp);
        log[9] = additionalsTemp[0];
        log[10] = additionalsTemp[1];
        log[12] = ' ';
        log[13] = ' ';
        
        log[20] = '$';
        log[21] = additionalsTemp[0];
        log[22] = additionalsTemp[1];
        log[23] = ',';
        log[24] = 'Y';
        log[26] = '@';
        log[28] = dataTemp[0];
        log[29] = dataTemp[1];
        log[31] = '=';
        log[33] = memTemp[2];
        log[34] = memTemp[3];
        break;
    default:
        break;
    }
}

void Logger::SetAddressingMode_16(uint16_t data, uint16_t mem, uint16_t additionals, uint8_t mode)
{
    // Put Char Representation of PC into an array
    char temp[4];
    word2hex(data, temp);

    char tempMem[4];
    char tempAdditionals[4];
    
    // Put Char Rep of PC into Log
    log[9] = temp[2];
    log[10] = temp[3];
    log[12] = temp[0];
    log[13] = temp[1];

    switch (mode)
    {
    // Others?
    case 0:
        log[20] = '$';
        log[21] = temp[0];
        log[22] = temp[1];
        log[23] = temp[2];
        log[24] = temp[3];
        break;
    // ABS
    case 1:
        log[20] = '$';
        log[21] = temp[0];
        log[22] = temp[1];
        log[23] = temp[2];
        log[24] = temp[3];

        byte2hex((uint8_t)(mem & 0xFF), tempMem);
        log[26] = '=';
        log[28] = tempMem[0];
        log[29] = tempMem[1];

        break;
    // IID
    case 2:
        word2hex(mem, tempMem);
        word2hex(additionals, tempAdditionals);
        
        log[9] = tempMem[2];
        log[10] = tempMem[3];
        log[12] = ' ';
        log[13] = ' ';

        log[20] = '(';
        log[21] = '$';
        log[22] = tempMem[2];
        log[23] = tempMem[3];
        log[24] = ',';
        log[25] = 'X';
        log[26] = ')';
        log[28] = '@';
        log[30] = tempAdditionals[2];
        log[31] = tempAdditionals[3];
        log[33] = '=';
        log[35] = temp[0];
        log[36] = temp[1];
        log[37] = temp[2];
        log[38] = temp[3];
        log[40] = '=';
        log[42] = tempMem[0];
        log[43] = tempMem[1];
        break;
    // IDI
    case 3:
        word2hex(mem, tempMem);
        word2hex(additionals, tempAdditionals);

        log[9] = tempMem[0];
        log[10] = tempMem[1];
        log[12] = ' ';
        log[13] = ' ';

        log[20] = '(';
        log[21] = '$';
        log[22] = tempMem[0];
        log[23] = tempMem[1];
        log[24] = ')';
        log[25] = ',';
        log[26] = 'Y';
        log[28] = '=';
        log[30] = tempAdditionals[0];
        log[31] = tempAdditionals[1];
        log[32] = tempAdditionals[2];
        log[33] = tempAdditionals[3];
        log[35] = '@';
        log[37] = temp[0];
        log[38] = temp[1];
        log[39] = temp[2];
        log[40] = temp[3];
        log[42] = '=';
        log[44] = tempMem[2];
        log[45] = tempMem[3];
        break;
    // IND
    case 4:
        word2hex(mem, tempMem);

        log[9] = tempMem[2];
        log[10] = tempMem[3];
        log[12] = tempMem[0];
        log[13] = tempMem[1];
        
        log[20] = '(';
        log[21] = '$';
        log[22] = tempMem[0];
        log[23] = tempMem[1];
        log[24] = tempMem[2];
        log[25] = tempMem[3];
        log[26] = ')';
        log[28] = '=';
        log[30] = temp[0];
        log[31] = temp[1];
        log[32] = temp[2];
        log[33] = temp[3];
        break;
    // ABY
    case 5:
        word2hex(mem, tempMem);
        word2hex(additionals, tempAdditionals);

        log[9] = tempMem[2];
        log[10] = tempMem[3];
        log[12] = tempMem[0];
        log[13] = tempMem[1];

        log[20] = '$';
        log[21] = tempMem[0];
        log[22] = tempMem[1];
        log[23] = tempMem[2];
        log[24] = tempMem[3];
        log[25] = ',';
        log[26] = 'Y';
        log[28] = '@';
        log[30] = temp[0];
        log[31] = temp[1];
        log[32] = temp[2];
        log[33] = temp[3];
        log[35] = '=';
        log[37] = tempAdditionals[2];
        log[38] = tempAdditionals[3];
        break;
    // ABX
    case 6:
        word2hex(mem, tempMem);
        word2hex(additionals, tempAdditionals);

        log[9] = tempMem[2];
        log[10] = tempMem[3];
        log[12] = tempMem[0];
        log[13] = tempMem[1];

        log[20] = '$';
        log[21] = tempMem[0];
        log[22] = tempMem[1];
        log[23] = tempMem[2];
        log[24] = tempMem[3];
        log[25] = ',';
        log[26] = 'X';
        log[28] = '@';
        log[30] = temp[0];
        log[31] = temp[1];
        log[32] = temp[2];
        log[33] = temp[3];
        log[35] = '=';
        log[37] = tempAdditionals[2];
        log[38] = tempAdditionals[3];
        break;
    default:
        break;
    }
}

// Takes in a 3 character string with instructions name
void Logger::SetInstructionName(string name)
{
    log[16] = name[0];
    log[17] = name[1];
    log[18] = name[2];
}

char *Logger::GetLog()
{
    return log;
}

void Logger::CompareTestLogs()
{
    // Open Test Log
    ifstream testLog;
    testLog.open("./logs/nestest.log", ios::in | ios::binary);

    if (!testLog.is_open())
    {
        cout << "testLog Cannot be Opened" << endl;
        return;
    }

    // Open My Log
    ifstream myLog;
    myLog.open("./logs/log.log", ios::in | ios::binary);

    if (!myLog.is_open())
    {
        cout << "myLog Cannot be Opened" << endl;
        return;
    }

    string testLine, myLine;

    while (getline(myLog, myLine) && getline(testLog, testLine))
    {
        if (!compareCStr(myLine.c_str(), testLine.c_str(), (size_t)73))
        {
            cout << "Unequal at Line: " << myLine << endl;
            testLog.close();
            myLog.close();
            return;
        }
    }

    // Close both logs
    testLog.close();
    myLog.close();
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

bool compareCStr(const char *str1, const char *str2, size_t endIndex)
{

    for (size_t i = 0; i < endIndex; i++)
    {
        if (*str1++ != *str2++)
        {
            return false;
        }
    }

    return true;
}