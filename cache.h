/*
Author: Cordell Hurst, Alex BOrtoc, Johnny Zhu
Course: CSCI 360, Computer Architecture III
Instructor: Xiaojie Zhang
Assignment: Software Simulator/Multi-Level Memory Memory Hierarchy
This program...

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

#ifndef __cache_H__
#define __cache_H__

#include <bitset>
#include <list>
#include <string>
#include <iostream>
#include <array>
#include <cmath>
#include <iomanip> //for cout.setf, etc

using namespace std;
//thought about inserting just the bitset into the array rather than this struct but I feel this gives us flexability to expand if reqired.
struct Register
{
	bitset<16> word; //dword - ie, 2 bytes per word - 16 bits
};

class cache
{
public:
	cache();
	//cache(int set_assoc, int word_num);
	//~cache();
	//Getters
	Register* getGeneralPurposeRegisters_GPRs(); //Returns list of registers
	bitset<16> getProgramCounter_PC();
	bitset<16> getGeneralPurposeRegisters_GPRs(int); //Returns selected General Purpose Register, 0-3
	bitset<16> getIndexRegister_X0();
	bitset<16> getInstructionRegister_IR();
	bitset<16> getMemoryAddressRegister_MAR();
	bitset<16> getMemoryBufferRegister_MBR();

	bitset<1> get_ZF();
	bitset<1> get_CF();
	bitset<1> get_SF();

	//Setters
	void resetAllRegisters();
	void setGeneralPurposeRegisters_GPRs(int, bitset<16>); //Sets selected General Purpose Register, 0-3, each is 16 bits (1 byte)
	void setIndexRegister_X0(bitset<16>);
	void setInstructionRegister_IR(bitset<16>);
	void setMemoryAddressRegister_MAR(bitset<16>);//set MemoryAddressRegister (0-4094) as bitset<16> - next instruction
	void setMemoryBufferRegister_MBR(bitset<16>);

	//two ways to set PC
    void set_ProgramCounter(bitset<16>);//(0-2047) as bitset<16>
	void set_ProgramCounter(int);//(0-2047)
	
	void set_ZF(int);
	void set_CF(int);
	void set_SF(int);
	
	//Utility
	void printRegisters(bool special = 0);
	void failCheck(istream &);//catches failed input cast and resets istream
	void increment_ProgramCounter();
	friend bitset<16> operator++ (bitset<16>&, int);//Postfix, ie bit_Set++; bitset<16> ONLY
	friend bitset<16> operator++ (bitset<16>&);//prefix, ie ++bit_Set; bitset<16> ONLY
	//friend bitset<16> operator> (bitset<16>&, bitset<16>&);
	//friend bitset<16> operator< (bitset<16>&, bitset<16>&);


	//cache design
	void setInstrCache(int, int, int);
	void printCache();
	void printHits();
	int getOffset();
	int getIndex();
	int getTag();
	void hitInc();
	void missInc();
	void replaceInc();
	int getTagValue(bitset<16> setIn);
	int getIndexValue(bitset<16> setIn);
	void addInstruction(bitset<16> setIn);
	bool getNotFull();
	void setNotFullTrue();
	void setNotFullFalse();
	
	struct BLOCK 
    {
        bitset<16> instruction;
        int block_tag = 0;
        bool valid = false;
        int timer = 0;
    };
    struct SET
    {
        BLOCK *blocks;
    };
private:
	Register GeneralPurposeRegisters_GPRs[4]; //Array of structs containing a bitset, 16 bits each, 0-3, referred to as R0 – R3. May be used as accumulators
	bitset<16> IndexRegister_X0; //HARD CODED IN OS CONSTRUCTOR //the index register contains 16-bit base address for base register addressing of memory.
	bitset<16> InstructionRegister_IR; //instruction to be executed
	bitset<16> MemoryAddressRegister_MAR; // 16 bit - address of the word to be fetched from memory (0-2047) as bitset<16>
	bitset<16> MemoryBufferRegister_MBR; //data just fetched from or stored into memory
	bitset<16> programCounter_PC; //address of next instruction to be executed (0-2047) as bitset<16>
	//bitset<6> programCounter_PC; //address of next instruction to be executed
	bitset<1> ZF;
	bitset<1> CF;
	bitset<1> SF;
	
	SET *cache_table;
	int set_size;
	int block_amount;
	int word_amount;
	int offset;
	int index;
	int tag;
	int miss = 0;
	int hit = 0;
	int replace = 0; 
	bool not_full;
};
#endif /* __cache_H__ */

