/*
Author: Cordell Hurst, Alex BOrtoc, Johnny Zhu
Course: CSCI 360, Computer Architecture III
Instructor: Xiaojie Zhang
Assignment: Software Simulator/Multi-Level Memory Memory Hierarchy
This program...
*/

#include "mainMemory.h"
#include <iomanip> //for cout.setf, etc

mainMemory::mainMemory()
{
	bitset<16>temp;
	for (int i = 0; i < 2048; i++)
		memory.push_back(temp);
	memory[23].flip(); //testing demo purpose
}

mainMemory::~mainMemory()
{
}
//returns instruction set list
list <bitset<16>> mainMemory::getInstructionSet()
{
	return instructionSet;
}
//returns next instruction in instruction set list
bitset<16> mainMemory::getNextInstruction()
{
	list <bitset<16>>::iterator iter = instructionSet.begin();
	bitset<16> temp = *iter;
	return temp;
}

void mainMemory::printMemory()
{
	
	int countFront= 0;
	int countBack = 2;
	cout << "\n";
	cout << right;
	cout << setw(50) << "Memory Display"
		<< "\n\t\t---------------------------------------------------";
	if (memory.empty())
		cout << "Memory is empty" << endl;
	memory[23].flip();
	for (int i = 0; i < 24; i++)
	{
		
		if ( i % 3 != 0)
		{
			cout << memory[i] << "   ";
		}
		else
		{
			cout << endl;
			cout << "\t" << setw(4) << setfill('0') << countFront << "-" << setw(4) << setfill('0') << countBack;
			cout << "   " << memory[i] << "   ";
		}
		countFront++;
		countBack++;
	}

	cout << "\n\t\t---------------------------------------------------\n"
		<< setw(29) << setfill(' ') << "R. Range Lookup" << setw(20) << setfill(' ') << "Q. Menu" << setw(20) << setfill(' ') << "H. Help"
		<< "\n\n\t==>> ";

	char input;
	do
	{
		cin >> input;
		cin.ignore(255, '\n');
		failCheck(cin);

		//calls for display of a range and help file needed
		if (input == 'H' || input == 'h')
			cout << "\t\nHelp File incomplete..." << endl;
		if (input == 'R' || input == 'r')
			cout << "\t\nRange Display incomplete..." << endl;

	}while(input != 'Q' && input != 'q');
}
//Removes all elements, leaving all containers with a size of 0.
void mainMemory::clearMemory()
{
	instructionSet.clear();//Removes all elements, leaving the container with a size of 0.
	memory.clear();//Removes all elements, leaving the container with a size of 0.
}
//"loads" instructions into main memory
void mainMemory::set_InstructionSet(list <bitset<16>> &instructionsIn)
{
	if (!instructionsIn.empty())
		instructionSet = instructionsIn;
	else
		cout << "No instructions to load!" << endl;
}

//catches failed input cast and resets istream
void mainMemory::failCheck(istream &cin)
{
	if (cin.fail())
	{
		cout << "Incorrect input:" << endl;
		cin.clear();
		cin.ignore(255, '\n');
	}
}

bitset<16> mainMemory::search(unsigned long address)
{
	return memory[address];
}