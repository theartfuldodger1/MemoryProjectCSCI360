/*
Author: Cordell Hurst, Alex BOrtoc, Johnny Zhu
Course: CSCI 360, Computer Architecture III
Instructor: Xiaojie Zhang
Assignment: Software Simulator/Multi-Level Memory Memory Hierarchy
This program...
*/
/*
Opcode  I  IX AC  Address
000001  0  0  11  101100
15  10  9  8  76  5    0
*/

#ifndef __OS_H__
#define __OS_H__

//#include "main_memory.h"
//#include "processor.h"
//#include "HDD.h"
#include "cache.h"
#include "mainMemory.h"
#include "bus.h"

#include <iostream>
#include <limits>
#include <fstream>
#include <iomanip> //for cout.setf, etc
#include <sstream>
#include <bitset>
#include <list>
#include <string>
//#include <vector>

using namespace std;

class OS
{
public:
	OS();
	~OS();

	void switchGo();//general selector switch for user functionality
	void failCheck(istream &cin);

	void initializationMenu();//main menu, Menu1
	unsigned short int menu1A();//add instruction file from Menu1, choice 1
	unsigned short int menu1B();// add individual instructions from Menu1, choice 2
	unsigned short int menu2();//simulation menu, follows addition of instructions (menu1A or 1B). Choice 1 returns the user to Menu 1 (Initialization Menu)
	unsigned short int menu2A();//follows loading of program into main memory - choice 3 from menu2/simulation menu 
	
	bitset<6> streamToOpCode(istream &cin);
	string opCodeToString(bitset<6>&);
	void processFile(istream & cin);//modified version of processFile, esp for istream cin
	void processFile(ifstream &inFile, list <bitset<16>>&);//For file processing only
	
	void loadInstructionsIntoMain();
	void clearAllData();

	//instruction display
	void printInstructions();//when isntructions are not yet loaded
	void stepInstructions();//instructions loaded in main memory
	void executeInstruction(bitset<16> &);//calls appropriate function to process an instruction based on instrcuction opCode
	void instructionDisplaySwitch(bitset<16> &);
	void printCodeRIXA(bitset<16> &);//for instruction display
	void printCodeIXA(bitset<16> &);//for instruction display
	void printCodeRimmed(bitset<16> &);//for instruction display
	void printCodeR(bitset<16> &);//for instruction display
	void printCodeRxRy(bitset<16> &);//for instruction display
	void printCodeRx(bitset<16> &);//for instruction display
	void printCodeRRII(bitset<16> &);//for instruction display

	//void voidLowerCase(string &wordIn);
	string fileIterator(istream &input, char delim);//uses either space, ' ' or ',' or '\n' as char delimeter per calling function requirements
	int scrollChars(istream &instructionFile);
	int scrollWhiteSpace(istream &cin);

	//Instruction encoding
	void codeRIXA(istream &inFile, bitset<16> &buildSet, bool);//Form --> opCode r, i, x, address;
	void codeIXA(istream &inFile, bitset<16> &buildSet, bool);//Form --> opCode i, x, address;
	void codeRimmed(istream &inFile, bitset<16> &buildSet, bool);//Form --> opCode r, immed;
    void codeR(istream &inFile, bitset<16> &buildSet, bool);//Form --> opCode r;
    void codeRxRy(istream &inFile, bitset<16> &buildSet, bool);//Form --> opCode rx, ry;
    void codeRx(istream &inFile, bitset<16> &buildSet, bool);//Form --> opCode rx;
    void codeRRII(istream &inFile, bitset<16> &buildSet, bool);//Form --> opCode, r, r, i, i;

	void encodeAddress(istream &inFile, bitset<16> &buildSet, bool);//encodes 6 bit address from user input or file
	bitset<16> effectiveAddress_EA(bitset<16> &); //accepts a bitset<16> instruction and returns its effective address as a bitset<16>

	void LDR(bitset<16> setIn); //Load register from memory
	void STR(bitset<16> setIn); //Store register to memory
	void LDX(bitset<16> setIn); //Load index register from memory
	void STX(bitset<16> setIn); //Store index register to memory
	void CMP(bitset<16> setIn); //Compares register value with memory location value

	void JE(bitset<16> setIn);
	void JNE(bitset<16> setIn);
	void JG(bitset<16> setIn);
	void JGE(bitset<16> setIn);
	void JL(bitset<16> setIn);
	void JLE(bitset<16> setIn);
	void JUMP(bitset<16> setIn);

	void AMR(bitset<16> setIn);
	void SMR(bitset<16> setIn);
	void AIR(bitset<16> setIn);
	void SIR(bitset<16> setIn);
	void DEC(bitset<16> setIn);
	void INC(bitset<16> setIn);
	void MUL(bitset<16> setIn);
	void DIV(bitset<16> setIn);
	void TER(bitset<16> setIn);
	void AND(bitset<16> setIn);
	void ORR(bitset<16> setIn);
	void NOT(bitset<16> setIn);
	void ADD(bitset<16> setIn);
	void SUB(bitset<16> setIn);

private:
	Bus SystemBus;
	cache MyCache;
	mainMemory MyMemory;
	list <bitset<16>> instructionSet_OS;//all instructions loaded here from file
	bool firstPassFlag = 0; //for stepInstructions()
	int constant = 107;
	unsigned int Pcount = 0;
};
#endif /* __OS_H__ */

