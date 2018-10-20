/*
 4 General Purpose Registers (GPRs), the four GPRs are numbered 0-3 and can be mnemonically referred to as R0 – R3. They may be used as accumulators.
 1 Index Registers, the index register is referred to as X0, contains a 16-bit base address that supports base register addressing of memory.
 1 Program Counter, address of next instruction to be executed, referred to as PC.
 1 Instruction Register, holds the instruction to be executed, referred to as IR.
 Memory Address Register MAR: holds the address of the word to be fetched from memory.
 Memory Buffer Register MBR: holds the data just fetched from or stored into memory.
*/
/*
Opcode  I  IX AC  Address
000001  0  0  11  101100
15  10  9  8  76  5    0
*/

#include "cache.h"

cache::cache()
{
	for (int i = 0; i < 4; i++)
	{
		Register GPR;
		GeneralPurposeRegisters_GPRs[i] = GPR;
		cout << i << " = " << GPR.word << endl;
	}
}

cache::~cache()
{
}
//holds 6 bit address of next instruction to be executed
bitset<6> cache::get_ProgramCounter_PC()
{
	return programCounter_PC;
}


//Returns list of registers
Register* cache::get_GeneralPurposeRegisters_GPRs()
{
	return GeneralPurposeRegisters_GPRs;
}
//Returns selected General Purpose Register Word, 0-3
bitset<16> cache::get_GeneralPurposeRegisters_GPRs(int intIn)
{
	return GeneralPurposeRegisters_GPRs[intIn].word;
}
//contains a 16-bit base address that supports base register addressing of memory
bitset<16> cache::get_IndexRegister_XO()
{
	return IndexRegister_XO;
}
//holds the 16 bit instruction to be executed
bitset<16> cache::get_InstructionRegister_IR()
{
	return InstructionRegister_IR;
}

bitset<6> cache::get_MemoryAddressRegister_MAR()
{
	return MemoryAddressRegister_MAR;
}
bitset<16> cache::get_MemoryBufferRegister_MBR()
{
	return MemoryBufferRegister_MBR;
}

//Sets selected General Purpose Register, 0-3
//accepts an int, representing one of the four register elements, and a 16 bit bitset as the data/instruction
void cache::set_GeneralPurposeRegisters_GPRs(int gprIn, bitset<16> setIn)
{
	GeneralPurposeRegisters_GPRs[gprIn].word = setIn;
}
void cache::set_IndexRegister_XO(bitset<16> setIn)
{
	IndexRegister_XO = setIn;
}
void cache::set_InstructionRegister_IR(bitset<16> setIn)
{
	InstructionRegister_IR = setIn;
}
void cache::set_MemoryAddressRegister_MAR(bitset<6> setIn)
{
	MemoryAddressRegister_MAR = setIn;
}
void cache::set_MemoryBufferRegister_MBR(bitset<16> setIn)
{
	MemoryBufferRegister_MBR = setIn;
}
void cache::set_ProgramCounter(bitset<6> instIn)
{
	programCounter_PC = instIn;
}

void cache::clear_AllRegisters()
{
	for (int i = 0; i < 4; i++)
		GeneralPurposeRegisters_GPRs[i].word.reset();

	IndexRegister_XO.reset();
	InstructionRegister_IR.reset();
	MemoryAddressRegister_MAR.reset();
	MemoryBufferRegister_MBR.reset();
}
void cache::printRegisters()
{

}