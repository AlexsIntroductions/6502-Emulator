#pragma once
#include <iostream>
#include <cstdint>
#include <string>
#include "../inc/nes_mem.h"

#define BIT_SHIFT(X) (1 << x)

#define N_FLAG BIT_SHIFT(7)
#define V_FLAG BIT_SHIFT(6)
#define B_FLAG BIT_SHIFT(4)
#define D_FLAG BIT_SHIFT(3)
#define I_FLAG BIT_SHIFT(2)
#define Z_FLAG BIT_SHIFT(1)
#define C_FLAG BIT_SHIFT(0)

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
  void evaluate(unsigned char opcocde);
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

  void AND();

  void ASL();

  void BCC();

  void BCS();

  void BEQ();

  void BIT();

  void BMI();

  void BNE();

  void BPL();

  void BRK();

  void BVC();

  void BVS();

  void CLC();

  void CLD();

  void CLI();

  void CLV();

  void CMP();

  void CPX();

  void CPY();

  void DEC();

  void DEX();

  void DEY();

  void EOR();

  void INC();

  void INX();

  void INY();

  void JMP();

  void JSR();

  void LDA();

  void LDX();

  void LDY();

  void LSR();

  void NOP();

  void ORA();

  void PHA();

  void PHP();

  void PLA();

  void PLP();

  void ROL();

  void ROR();

  void RTI();

  void RTS();

  void SBC();

  void SEC();

  void SED();

  void SEI();

  void STA();

  void STX();

  void STY();

  void TAX();

  void TAY();

  void TSX();

  void TXA();

  void TXS();

  void TYA();
};