/*
Author: Cordell Hurst, Alex BOrtoc, Johnny Zhu
Course: CSCI 360, Computer Architecture III
Instructor: Xiaojie Zhang
Assignment: Software Simulator/Multi-Level Memory Memory Hierarchy
This program...
*/

#ifndef __MAINMEMORY_H__
#define __MAINMEMORY_H__

#include <bitset>
#include <list>
#include <vector>
#include <iostream>

using namespace std;

//need to complete definition of this class according to procject spec
class mainMemory
{
public:
	mainMemory();
	~mainMemory();
	list <bitset<16>> getInstructionSet();//returns instruction set list
	bitset<16> getNextInstruction();//returns next instruction in instruction set list
	void set_InstructionSet(list <bitset<16>> &);
	void clearMemory();
	void printMemory();
	void failCheck(istream &cin);
private:
	list <bitset<16>> instructionSet;//all instructions loaded here from file
	vector <bitset<16>> memory;
};
#endif /*__MAINMEMORY_H__*/

