#include "../inc/log.h"

using namespace std;

bool compareCStr(const char *str1, const char *str2, size_t endIndex);
void byte2hex(uint8_t input, char *output);
void word2hex(uint16_t input, char *output);

Logger::Logger()
{
    // Remove Old Log File
    remove("./logs/log.log");

    // default set mode
    logMode = 0;

    // default length
    length = 100;

    // Set the Log String to White Space
    for (int i = 0; i < 100; i++)
    {
        log[i] = ' ';
    }
}

Logger::Logger(int mode)
{
    // Remove Old Log File
    remove("./logs/log.log");

    // Set the Log String to White Space
    for (int i = 0; i < 100; i++)
    {
        log[i] = ' ';
    }

    // set mode
    logMode = mode;
}

Logger::~Logger() {}

void Logger::Log()
{
    switch(logMode){
        case 0:
            SetMode0();
            break;
        case 1:
            SetMode1();
            break;
        default:
            SetMode0();
            break;
    }


    if (!ofstream("./logs/log.log", ios::app | ios::binary | ios::out).write(log, length))
    {
        cout << "Failed to Write to Log File" << endl;
    }

    for(int i = 0; i < 99; i++){
        log[i] = ' ';
    }
}

void Logger::SetMode(int mode){
    logMode = mode;
}

void Logger::SetPC(uint16_t data)
{
    // Put Char Representation of PC into an array
    word2hex(data, pc);
}

void Logger::SetOpcode(uint8_t data)
{
    // Put Char Representation of PC into an array
    byte2hex(data, opcode);
}

void Logger::SetAcc(uint8_t data)
{
    // Put Char Representation of PC into an array
    byte2hex(data, acc);
}

void Logger::SetX(uint8_t data)
{
    // Put Char Representation of X into an array
    byte2hex(data, x);
}

void Logger::SetY(uint8_t data)
{
    // Put Char Representation of Y into an array
    byte2hex(data, y);
}

void Logger::SetStatus(uint8_t data)
{
    // Put Char Representation of status into an array
    byte2hex(data, status);
}

void Logger::SetStackPointer(uint8_t data)
{
    // Put Char Representation of stack pointer into an array
    byte2hex(data, sp);
}

void Logger::SetCycles(int data){
    sprintf(cycles, "%d", data);
}

void Logger::SetAddressingMode(uint16_t data, uint16_t mem, uint16_t additionals, uint8_t mode){
    switch (logMode)
    {
    case 0:
        SetAddressingMode0(data, mem, additionals, mode);
        break;
    case 1:
        break;
    default:
        SetAddressingMode0(data, mem, additionals, mode);
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

void Logger::CompareNesTestLogs()
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

        // for(int i = 86; i < 95; i++){
        //     if(myLine.at(i) != testLine.at(i)){
        //         cout << "Unequal at Line: " << myLine << endl;
        //         testLog.close();
        //         myLog.close();
        //         return;
        //     }
        // }
    }
    // Close both logs
    testLog.close();
    myLog.close();
}

void Logger::CompareNesTestv2Logs()
{
    // Open Test Log
    ifstream testLog;
    testLog.open("./logs/nestest-v2.log", ios::in | ios::binary);

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
        while(testLine.at(0) == ' '){
            getline(testLog, testLine);
        }
        if (myLine != testLine)
        {
            cout << "Unequal at Line: " << endl << myLine << endl << testLine << endl;
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
        if (str1[i] != str2[i])
        {
            cout << "Unequal at Char: " << i << endl;
            cout << str1[i] << " != " << str2[i] << endl;
            cout << str1 << endl;
            cout << str2 << endl;
            return false;
        }
    }

    return true;
}

void Logger::SetMode0(){
    /** Structure of Log Entry
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

    log[74] = 'P';
    log[75] = 'P';
    log[76] = 'U';
    log[77] = ':';

    log[81] = ',';

    log[86] = 'C';
    log[87] = 'Y';
    log[88] = 'C';
    log[89] = ':';

    log[99] = '\n';

    // Copy Program Counter to log array
    for (unsigned int i = 0; i < 4; i++)
    {
        log[i] = pc[i];
    }

    // Copy opcode to log array
    log[6] = opcode[0];
    log[7] = opcode[1];

    // Copy Acc to log array
    log[50] = acc[0];
    log[51] = acc[1];

    // Copy X to log array
    log[55] = x[0];
    log[56] = x[1];

    // Copy Y to log array
    log[60] = y[0];
    log[61] = y[1];

    // Copy status to log array
    log[65] = status[0];
    log[66] = status[1];

    // Copy stack pointer to log array
    log[71] = sp[0];
    log[72] = sp[1];

    // set cycles
    for(int i = 0; i < sizeof(int)*8+1; i++){
        if(cycles[i] == '\0'){ return; }
        log[90 + i] = cycles[i];
    }

    length = 100;
}

void Logger::SetAddressingMode0(uint16_t data, uint16_t mem, uint16_t additionals, uint8_t mode)
{
    // Put Char Representation of PC into an array
    char temp[4];
    word2hex(data, temp);

    char tempMem[4];
    char tempAdditionals[4];
    
    // Display bytes after opcode
    // 1 byte addressing modes
    if(mode >= 7 && mode != 10){
        log[9] = temp[2];
        log[10] = temp[3];
    }
    // 0 byte addressing modes
    else if(mode == 10){
    }
    // 2 byte addressing modes
    else{
        // Put Char Rep of PC into Log
        log[9] = temp[2];
        log[10] = temp[3];
        log[12] = temp[0];
        log[13] = temp[1];
    }


    switch (mode)
    {
    // Others?
    case 0:
        log[9] = temp[2];
        log[10] = temp[3];
        log[12] = temp[0];
        log[13] = temp[1];
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
        // Imm
    case 7:
        log[20] = '#';
        log[21] = '$';
        log[22] = temp[2];
        log[23] = temp[3];
        break;
    // ZPG
    case 8:
        byte2hex((uint8_t)mem & 0xFF, tempMem);
        log[20] = '$';
        log[21] = temp[2];
        log[22] = temp[3];
        log[24] = '=';
        log[26] = tempMem[0];
        log[27] = tempMem[1];
        break;
    // REL
    case 9:
        (data & 0x80) ? (mem -= (((uint8_t)255 - data) + 1)) : (mem += data);
        word2hex(mem, tempMem);
        log[20] = '$';
        log[21] = tempMem[0];
        log[22] = tempMem[1];
        log[23] = tempMem[2];
        log[24] = tempMem[3];
        break;
    // ACC
    case 10:
        log[20] = 'A';
        break;
    // ZPX
    case 11:
        word2hex(mem, tempMem);
        byte2hex(additionals, tempAdditionals);
        log[9] = temp[2];
        log[10] = temp[3];
        log[12] = ' ';
        log[13] = ' ';
        
        log[20] = '$';
        log[21] = temp[2];
        log[22] = temp[3];
        log[23] = ',';
        log[24] = 'X';
        log[26] = '@';
        log[28] = tempAdditionals[0];
        log[29] = tempAdditionals[1];
        log[31] = '=';
        log[33] = tempMem[2];
        log[34] = tempMem[3];
        break;
    // ZPY
    case 12:
        word2hex(mem, tempMem);
        byte2hex(additionals, tempAdditionals);
        log[9] = tempAdditionals[0];
        log[10] = tempAdditionals[1];
        log[12] = ' ';
        log[13] = ' ';
        
        log[20] = '$';
        log[21] = tempAdditionals[0];
        log[22] = tempAdditionals[1];
        log[23] = ',';
        log[24] = 'Y';
        log[26] = '@';
        log[28] = temp[2];
        log[29] = temp[3];
        log[31] = '=';
        log[33] = tempMem[2];
        log[34] = tempMem[3];
        break;
    default:
        break;
    }
}

void Logger::SetMode1(){
    /** Structure of Log Entry
     *  [0:3] - program counter
     *  [6:9] - Accumulator
     *  [11:14] - X
     *  [16:19] - Y
     *  [21:24] - Status
     *  [26:30] - Stack Pointer
     *  [32:end] - Cycles
    */
    // Set Formatting
    log[6] = 'A';
    log[7] = ':';

    log[11] = 'X';
    log[12] = ':';

    log[16] = 'Y';
    log[17] = ':';

    log[21] = 'P';
    log[22] = ':';

    log[26] = 'S';
    log[27] = 'P';
    log[28] = ':';

    log[32] = 'C';
    log[33] = 'P';
    log[34] = 'U';
    log[35] = 'C';
    log[36] = ':';

    // Write PC to Log
    log[0] = pc[0];
    log[1] = pc[1];
    log[2] = pc[2];
    log[3] = pc[3];

    // Write Acc to Log
    log[8] = acc[0];
    log[9] = acc[1];

    // Write X to Log
    log[13] = x[0];
    log[14] = x[1];

    // Write Y to Log
    log[18] = y[0];
    log[19] = y[1];

    // Write Status to Log
    log[23] = status[0];
    log[24] = status[1];

    // Write PC to Log
    log[29] = sp[0];
    log[30] = sp[1];

    // Write Cycles to Log
    for(int i = 0; i < sizeof(int)*8+1; i++){
        if(cycles[i] == '\0'){ log[37 + i] = '\n'; length = 38 + i; return; }
        log[37 + i] = cycles[i];
    }
}

