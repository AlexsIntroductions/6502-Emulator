#pragma once
#include <iostream>
#include <cstdint>
#include <string>
#include "../inc/nes_mem.h"
#include "../inc/log.h"

#define N_FLAG 0b10000000
#define V_FLAG 0b01000000
#define B_FLAG 0b00010000
#define D_FLAG 0b00001000
#define I_FLAG 0b00000100
#define Z_FLAG 0b00000010
#define C_FLAG 0b00000001

#define N_FLAG_INV ~N_FLAG
#define V_FLAG_INV ~V_FLAG
#define B_FLAG_INV ~B_FLAG
#define D_FLAG_INV ~D_FLAG
#define I_FLAG_INV ~I_FLAG
#define Z_FLAG_INV ~Z_FLAG
#define C_FLAG_INV ~C_FLAG

// #define CPU_DEBUG
#define CPU_LOG

/*
Zero Page           :   [0x0000 … 0x00FF]
STACK               :   [0x0100 … 0x01FF]
Programmer Use      :   [0x0200 … 0x1FFF]
NES MODULES         :   [0x2000 … 0x4020]
CARTRIDGE RAM       :   [0x6000 … 0x7FFF]
PROGRAM ROM         :   [0x8000 … 0xFFFF]
  -NMI handler      :   [0xFFFA … 0xFFFB]
  -Power On Reset   :   [0xFFFC … 0xFFFD]
  -BRK/IIRQ         :   [0xFFFE … 0xFFFF]

*/

class nes_cpu
{
  typedef uint16_t (nes_cpu::*AddressingMode)();
  typedef void (nes_cpu::*Instruction)(uint16_t);
  //----------General Registers----------//
  // Accumulator
  uint8_t a;
  // X register
  uint8_t x;
  // Y register
  uint8_t y;
  //----------Status Register----------//
  // 7 - N: negative result
  // 6 - V: overflow
  // 5 -
  // 4 - B: break
  // 3 - D: decimal mode
  // 2 - I: interrupt disable
  // 1 - Z: zero result
  // 0 - C: carry
  uint8_t status;
  //----------Stack Pointer----------//
  uint8_t sp;
  //----------Address Bus?----------//
  uint16_t pc;

  int cycles = 0;

  nes_mem *mem;

public:
  Logger cpuLogger;
  // Init Functions
  nes_cpu();
  ~nes_cpu();

  // Component Functions
  void evaluate();
  void set_mem(nes_mem *_mem);
  void set_pc(uint16_t address);

  // Helper Functions
  void print_CPU_state();

private:


  // Addressing Mode Functions
  // return the byte of data that is to be acted on

  // Implicit
  uint16_t IMP();
  // Accumulator
  uint16_t ACC();
  // Immediate
  uint16_t IMM();
  // Zero Page
  uint16_t ZPG();
  uint16_t ZPG_MEM();
  // Zero Page X
  uint16_t ZPX();
  uint16_t ZPX_MEM();
  // Zero Page Y
  uint16_t ZPY();
  uint16_t ZPY_MEM();
  // Relative
  uint16_t REL();
  // Absolute
  uint16_t ABS();
  uint16_t ABS_MEM();
  uint16_t JMP_ABS();
  // Absolute X
  uint16_t ABX();
  uint16_t ABX_MEM();
  // Absolute Y
  uint16_t ABY();
  uint16_t ABY_MEM();
  // Indirect
  uint16_t IND();
  // Indexed Indirect
  uint16_t IID();
  uint16_t IID_MEM();
  // Indirect Indexed
  uint16_t IDI();
  uint16_t IDI_MEM();

  void bytes2hex(unsigned char *src, char *out, int len);

  // Instruction functions
  void ADC(uint16_t val);

  void AND(uint16_t val);

  void ASL(uint16_t val);
  void ASL_ACC(uint16_t val);

  void BCC(uint16_t offset);

  void BCS(uint16_t offset);

  void BEQ(uint16_t offset);

  void BIT(uint16_t val);

  void BMI(uint16_t offset);

  void BNE(uint16_t offset);

  void BPL(uint16_t offset);

  void BRK(uint16_t val);

  void BVC(uint16_t offset);

  void BVS(uint16_t offset);

  void CLC(uint16_t val);

  void CLD(uint16_t val);

  void CLI(uint16_t val);

  void CLV(uint16_t val);

  void CMP(uint16_t val);

  void CPX(uint16_t val);

  void CPY(uint16_t val);

  void DEC(uint16_t address);

  void DEX(uint16_t val);

  void DEY(uint16_t val);

  void EOR(uint16_t val);

  void INC(uint16_t address);

  void INX(uint16_t val);

  void INY(uint16_t val);

  void JMP(uint16_t address);

  void JSR(uint16_t address);

  void LDA(uint16_t val);

  void LDX(uint16_t val);

  void LDY(uint16_t val);

  void LSR(uint16_t address);
  void LSR_ACC(uint16_t address);

  void NOP(uint16_t val);

  void ORA(uint16_t val);

  void PHA(uint16_t val);

  void PHP(uint16_t val);

  void PLA(uint16_t val);

  void PLP(uint16_t val);

  void ROL(uint16_t address);
  void ROL_ACC(uint16_t address);

  void ROR(uint16_t address);
  void ROR_ACC(uint16_t address);

  void RTI(uint16_t val);

  void RTS(uint16_t val);

  void SBC(uint16_t val);

  void SEC(uint16_t val);

  void SED(uint16_t val);

  void SEI(uint16_t val);

  void STA(uint16_t address);

  void STX(uint16_t address);

  void STY(uint16_t address);

  void TAX(uint16_t val);

  void TAY(uint16_t val);

  void TSX(uint16_t val);

  void TXA(uint16_t val);

  void TXS(uint16_t val);

  void TYA(uint16_t val);
protected:
  // First Index: Hi Nibble, Second Index: Lo Nibble
  pair<Instruction, AddressingMode> opcodeEval[16][16] = {
    {{BRK,IMP}, {ORA, IID_MEM}, {NOP, IMP}, {NOP, IMP}, {NOP, IMP}, {ORA, ZPG_MEM}, {ASL, ZPG}, {NOP, IMP}, {PHP, IMP}, {ORA, IMM}, {ASL_ACC, ACC}, {NOP, IMP}, {NOP, IMP}, {ORA, ABS_MEM}, {ASL, ABS}, {NOP, IMP}},
    {{BPL, REL}, {ORA, IDI_MEM}, {NOP, IMP}, {NOP, IMP}, {NOP, IMP}, {ORA, ZPX_MEM}, {ASL, ZPX}, {NOP, IMP}, {CLC, IMP}, {ORA, ABY_MEM}, {NOP, IMP}, {NOP, IMP}, {NOP, IMP}, {ORA, ABX_MEM}, {ASL, ABX}, {NOP, IMP}},
    {{JSR, JMP_ABS}, {AND, IID_MEM}, {NOP, IMP}, {NOP, IMP}, {BIT, ZPG_MEM}, {AND, ZPG_MEM}, {ROL, ZPG}, {NOP, IMP}, {PLP, IMP}, {AND, IMM}, {ROL_ACC, ACC}, {NOP, IMP}, {BIT, ABS_MEM}, {AND, ABS_MEM}, {ROL, ABS}, {NOP, IMP}},
    {{BMI, REL}, {AND, IDI_MEM}, {NOP, IMP}, {NOP, IMP}, {NOP, IMP}, {AND, ZPX_MEM}, {ROL, ZPX}, {NOP, IMP}, {SEC, IMP}, {AND, ABY_MEM}, {NOP, IMP}, {NOP, IMP}, {NOP, IMP}, {AND, ABX_MEM}, {ROL, ABX}, {NOP, IMP}},
    {}
  };
};