#pragma once
#include <iostream>
#include <cstdint>
#include <string>
#include "../inc/nes_mem.h"

#define BIT_SHIFT_8(X) (1 << x)
#define INV_BIT_SHIFT_8(X) (0b11111111 ^ (1 << X))

#define N_FLAG BIT_SHIFT_8(7)
#define V_FLAG BIT_SHIFT_8(6)
#define B_FLAG BIT_SHIFT_8(4)
#define D_FLAG BIT_SHIFT_8(3)
#define I_FLAG BIT_SHIFT_8(2)
#define Z_FLAG BIT_SHIFT_8(1)
#define C_FLAG BIT_SHIFT_8(0)

#define N_FLAG_INV INV_BIT_SHIFT_8(7)
#define V_FLAG_INV INV_BIT_SHIFT_8(6)
#define B_FLAG_INV INV_BIT_SHIFT_8(4)
#define D_FLAG_INV INV_BIT_SHIFT_8(3)
#define I_FLAG_INV INV_BIT_SHIFT_8(2)
#define Z_FLAG_INV INV_BIT_SHIFT_8(1)
#define C_FLAG_INV INV_BIT_SHIFT_8(0)



/*
RAM                     :   [0x0000 … 0x2000]
  -Zero Page        :   [0x0000 … 0x00FF]
  -STACK            :   [0x0100 … 0x01FF]
NES MODULES             :   [0x2000 … 0x4020]
CARTRIDGE RAM           :   [0x6000 … 0x8000]
PROGRAM ROM             :   [0x8000 … 0xFFFF]
  -NMI handler      :   [0xFFFA … 0xFFFB]
  -Power On Reset   :   [0xFFFC … 0xFFFD]
  -BRK/IntReqHandler:   [0xFFFE … 0xFFFF]

*/

class nes_cpu
{

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

  int debug = 0;

public:
  nes_cpu();
  ~nes_cpu();
  void evaluate();
  void set_mem(nes_mem *_mem);
  void print_CPU_state();

  // Debug Functions
  void set_debug(int val);

private:
  // Addressing Mode Functions
  // return the byte of data that is to be acted on

  // Implicit
  void IMP();
  // Accumulator
  uint8_t ACC();
  // Immediate
  uint8_t IMM();
  // Zero Page
  uint8_t ZPG();
  // Zero Page X
  uint8_t ZPX();
  // Zero Page Y
  uint8_t ZPY();
  // Relative
  int8_t REL();
  // Absolute
  uint16_t ABS();
  // Absolute X
  uint16_t ABX();
  // Absolute Y
  uint16_t ABY();
  // Indirect
  uint16_t IND();
  // Indexed Indirect
  uint16_t IID();
  // Indirect Indexed
  uint16_t IDI();

  void bytes2hex(unsigned char *src, char *out, int len);

  // Instruction functions
  void ADC(uint8_t val);

  void AND(uint8_t val);

  void ASL(uint8_t* val);

  void BCC(uint8_t offset);

  void BCS(uint8_t offset);

  void BEQ(uint8_t offset);

  void BIT(uint8_t val);

  void BMI(uint8_t offset);

  void BNE(uint8_t offset);

  void BPL(uint8_t offset);

  void BRK();

  void BVC(uint8_t offset);

  void BVS(uint8_t offset);

  void CLC();

  void CLD();

  void CLI();

  void CLV();

  void CMP(uint8_t val);

  void CPX(uint8_t val);

  void CPY(uint8_t val);

  void DEC(uint8_t* val);

  void DEX();

  void DEY();

  void EOR(uint8_t val);

  void INC(uint8_t* val);

  void INX();

  void INY();

  void JMP(uint16_t address);

  void JSR(uint16_t address);

  void LDA(uint8_t val);

  void LDX(uint8_t val);

  void LDY(uint8_t val);

  void LSR(uint8_t* val);

  void NOP();

  void ORA(uint8_t val);

  void PHA();

  void PHP();

  void PLA();

  void PLP();

  void ROL(uint8_t* val);

  void ROR(uint8_t* val);

  void RTI();

  void RTS();

  void SBC(uint8_t val);

  void SEC();

  void SED();

  void SEI();

  void STA(uint16_t address);

  void STX(uint16_t address);

  void STY(uint16_t address);

  void TAX();

  void TAY();

  void TSX();

  void TXA();

  void TXS();

  void TYA();
};