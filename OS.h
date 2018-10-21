/*
Author: Cordell Hurst
Course: 340, Operating Systems
Instructor: Prof Pavel Shostak
Assignment: OperatingSystem/Memory Management Simulation
computer
*/
/*
Opcode  I  IX AC  Address
000001  0  0  11  101100
15  10  9  8  76  5    0
*/
#pragma once

#ifndef __OS_H__
#define __OS_H__

//#include "main_memory.h"
//#include "processor.h"
//#include "HDD.h"
#include "cache.h"
#include "mainMemory.h"

#include <iostream>
#include <limits>
#include <fstream>
#include <iomanip> //for cout.setf, etc
#include <sstream>
#include <bitset>
#include <list>
#include <string>

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

	void processFile(ifstream &inFile, list <bitset<16>>&);//
	void processFile(istream & cin);//
	//void voidLowerCase(string &wordIn);
	string fileIterator(istream &input, char delim);//uses either space, ' ' or ',' or '\n' as char delimeter per calling function requirements
	int scrollChars(istream &instructionFile);
	int scrollWhiteSpace(istream &cin);

	//instruction encoding
	void codeRIXA(istream &inFile, bitset<16> &buildSet, bool);//Form --> opCode r, i, x, address;
	void codeIXA(istream &inFile, bitset<16> &buildSet, bool);//Form --> opCode i, x, address;
	void codeRimmed(istream &inFile, bitset<16> &buildSet, bool);//Form --> opCode r, immed;
    void codeR(istream &inFile, bitset<16> &buildSet, bool);//Form --> opCode r;
    void codeRxRy(istream &inFile, bitset<16> &buildSet, bool);//Form --> opCode rx, ry;
    void codeRx(istream &inFile, bitset<16> &buildSet, bool);//Form --> opCode rx;
    void codeRRII(istream &inFile, bitset<16> &buildSet, bool);//Form --> opCode, r, r, i, i;

	void encodeAddress(istream &inFile, bitset<16> &buildSet, bool);//encodes 6 bit address from user input or file

private:
	cache MyCache;
	mainMemory MyMemory;
	bitset<6> streamToOpCode(istream &cin);
	list <bitset<16>> InstructionSet_OS;//all instructions loaded here from file
};
#endif /* __OS_H__ */

