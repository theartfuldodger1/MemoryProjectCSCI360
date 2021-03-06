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
	
	//testing demo purpose below
	memory[9].flip();
	memory[23].set(1, 1);
	memory[23].set(3, 1);
	memory[23].set(6, 1);
	memory[23].set(7, 1);
	memory[23].set(11, 1);
	
}

mainMemory::~mainMemory()
{
}

//returns instruction set vector
vector <bitset<16>> mainMemory::getInstructionSet()
{
	return memory;
}
//returns next instruction in instruction set list
bitset<16> mainMemory::getInstruction(bitset<16> programCounter_In)
{
	unsigned long tempLong = programCounter_In.to_ulong();
	bitset<16> tempInstruction = memory[tempLong];
	return tempInstruction;
}
//returns data stored at the specified location
/*int mainMemory::getData(unsigned long address)
{
	return memory[address].instruction.to_ulong();
}*/
//returns the bitset stored at the specified location
bitset<16> mainMemory::getInstruction(unsigned long address)
{
	return memory[address];
}
//"loads" instructions into main memory accoring to address/EA
void mainMemory::insertInstruction(bitset<16> &instructionsIn, bitset<16> &effectiveAddress_EA)
{
	//cout << "EA: " << effectiveAddress_EA << endl;
	memory[effectiveAddress_EA.to_ulong()] = instructionsIn;
}
//"loads" instructions into main memory accoring to sequence
void mainMemory::insertInstruction(bitset<16> &instructionsIn, int count)
{
	//cout << "EA: " << effectiveAddress_EA << endl;
	memory[count] = instructionsIn;
}
//sets the bitset at specified location to the provided value
void mainMemory::setMemoryElement(unsigned long address, bitset<16> setIn)
{
	memory[address] = setIn;
}
//countFront and countBack default to 0, if ONLY instStart param is present in call. IN OTHER WORDS, ONLY instStart is required to call
//If do not want the memory print to start at 0 - you must provide the element you want to start at as param 2 - countFront
/*void mainMemory::printMemory(int instStart, int countFront)
{
	char input;
	int i = instStart;//for loop param - instStart == first element of instruction block in MM
	int countBack = countFront + 1;
	int endOfMemory = 2048;//adjust hardcoded number to where you want memory to stop during normal printq
	int distance = 32;//how may loops you want to print befor pausing for input or just plain stopping print.

	bool specialCall = 0;
	int countFrontCheck;
	if(countFront != 0)
	{
		specialCall = 1;
		countFrontCheck = countFront;
		endOfMemory = instStart + distance;//adjust hardcoded number to where you want memory to stop during special print
	}

	cout << "\n";
	cout << right;
	cout << setw(70) << "Memory Display"
		<< "\n\t------------------------------------------------------------------------------------------------------------------\n";
	if (memory.empty())
		cout << "Memory is empty" << endl;
	for (; i < endOfMemory; i++)
	{
		
		if ( i % 3 != 0)
		{
			cout << "\t" << setw(4) << setfill('0') << countFront << "-" << setw(4) << setfill('0') << countBack;
			cout << "   " << memory[i] << " " << memory[i].to_ulong() << "   ";
		}
		else
		{
			cout << endl;
			cout << "\t" << setw(4) << setfill('0') << countFront << "-" << setw(4) << setfill('0') << countBack;
			cout << "   " << memory[i] << " " << memory[i].to_ulong() << "   ";
		}
		if (!specialCall)
		{
			if (countFront != 0 && i % distance == 0)
			{
				cout << "\n\t------------------------------------------------------------------------------------------------------------------"
					<< "\n\n\tMore memory elements exist. You can enter Q to quit or continue by entering any other key. "
					<< "\n\n\t==>> ";
				cin >> input;
				cin.ignore(255, '\n');
				failCheck(cin);
				if (input == 'Q' || input == 'q')
					break;
			}
		}
		countFront += 2;
		countBack += 2;
	}
	cout << "\n\t------------------------------------------------------------------------------------------------------------------";
	if(!specialCall)
	{
		cout << setw(52) << setfill(' ') << "R. Range Lookup" << setw(20) << setfill(' ') << "Q. Menu" << setw(20) << setfill(' ') << "H. Help"
		<< "\n\n\t==>> ";

	
		do
		{
			cin >> input;
			cin.ignore(255, '\n');
			failCheck(cin);

			//calls for display of a range and help file needed
			if (input == 'H' || input == 'h')
				cout << "\t\nHelp File incomplete..." << endl;
			if (input == 'R' || input == 'r'){
				string from;
				string to;
				cout << "\n\n\t\tFrom?" << endl;
				cin >> from;
				cout << "\n\n\t\tTo?" << endl;
				cin >> to;
				int start = stoi(from);
				int end = stoi(to);
				start = start - (start % 3);		//sets it to the first number of the first line to be displayed
				end = end - (end % 3) + 2;			//sets it to the last number of the last line to be displayed
				countFront = start;
				countBack = start + 2;
				cout << setw(70) << "Memory Display"
					<< "\n\t------------------------------------------------------------------------------------------------------------------\n";
			
				for (int i = start; i <= end; i++)
				{
					if (i % 3 != 0)
					{
						cout << "\t" << setw(4) << setfill('0') << countFront << "-" << setw(4) << setfill('0') << countBack;
						cout << "   " << memory[i] << " " << memory[i].to_ulong() << "   ";
					}
					else
					{
						cout << endl;
						cout << "\t" << setw(4) << setfill('0') << countFront << "-" << setw(4) << setfill('0') << countBack;
						cout << "   " << memory[i] << " " << memory[i].to_ulong() << "   ";
					}
					countFront++;
					countBack++;
				}
				cout << "\n\t------------------------------------------------------------------------------------------------------------------\n"
					<< setw(52) << setfill(' ') << "R. Range Lookup" << setw(20) << setfill(' ') << "Q. Menu" << setw(20) << setfill(' ') << "H. Help"
					<< "\n\n\t==>> ";
			}
		}while(input != 'Q' && input != 'q');
	}
}*/
void mainMemory::printMemory()
{
	char input;

	cout << "\n";
	cout << right;
	cout << setw(70) << "Memory Display"
		<< "\n\t------------------------------------------------------------------------------------------------------------------";

	int countFront = 0;
	int countBack = 1;

	if (memory.empty())
		cout << "Memory is empty" << endl;
	for (int i = 0; i < 2048; i++)
	{

		if (i % 3 != 0)
		{
			cout << "\t" << setw(4) << setfill('0') << countFront << "-" << setw(4) << setfill('0') << countBack;
			cout << "   " << memory[i] << " " << memory[i].to_ulong() << "   ";
		}
		else
		{
			cout << endl;
			cout << "\t" << setw(4) << setfill('0') << countFront << "-" << setw(4) << setfill('0') << countBack;
			cout << "   " << memory[i] << " " << memory[i].to_ulong() << "   ";
		}

		if (countFront != 0 && i % 60 == 0)
		{
			cout << "\n\t------------------------------------------------------------------------------------------------------------------"
				<< "\n\n\tMore memory elements exist. You can enter Q to quit or continue by entering any other key. "
				<< "\n\n\t==>> ";
			cin >> input;
			cin.ignore(255, '\n');
			failCheck(cin);
			if (input == 'Q' || input == 'q')
				break;
		}
		countFront += 2;
		countBack += 2;
	}
	cout << "\n\t------------------------------------------------------------------------------------------------------------------\n"
		<< setw(52) << setfill(' ') << "R. Range Lookup" << setw(20) << setfill(' ') << "Q. Menu" << setw(20) << setfill(' ') << "H. Help"
		<< "\n\n\t==>> ";


	do
	{
		cin >> input;
		cin.ignore(255, '\n');
		failCheck(cin);

		//calls for display of a range and help file needed
		if (input == 'H' || input == 'h')
			cout << "\t\nHelp File incomplete..." << endl;
		if (input == 'R' || input == 'r') {
			string from;
			string to;
			cout << "\n\n\t\tFrom?" << endl;
			cin >> from;
			cout << "\n\n\t\tTo?" << endl;
			cin >> to;
			int start = stoi(from);
			int end = stoi(to);
			start = start - (start % 3);		//sets it to the first number of the first line to be displayed
			end = end - (end % 3) + 2;			//sets it to the last number of the last line to be displayed
			countFront = start;
			countBack = start + 2;
			cout << setw(70) << "Memory Display"
				<< "\n\t------------------------------------------------------------------------------------------------------------------";

			for (int i = start; i <= end; i++)
			{
				if (i % 3 != 0)
				{
					cout << "\t" << setw(4) << setfill('0') << countFront << "-" << setw(4) << setfill('0') << countBack;
					cout << "   " << memory[i] << " " << memory[i].to_ulong() << "   ";
				}
				else
				{
					cout << endl;
					cout << "\t" << setw(4) << setfill('0') << countFront << "-" << setw(4) << setfill('0') << countBack;
					cout << "   " << memory[i] << " " << memory[i].to_ulong() << "   ";
				}
				countFront++;
				countBack++;
			}
			cout << "\n\t------------------------------------------------------------------------------------------------------------------\n"
				<< setw(52) << setfill(' ') << "R. Range Lookup" << setw(20) << setfill(' ') << "Q. Menu" << setw(20) << setfill(' ') << "H. Help"
				<< "\n\n\t==>> ";
		}
	} while (input != 'Q' && input != 'q');
}
//Removes all elements, leaving all containers with a size of 0.
void mainMemory::clearMemory()
{
	//instructionSet.clear();//Removes all elements, leaving the container with a size of 0.
	//memory.clear();//Removes all elements, leaving the container with a size of 0.

	for (int i = 0; i < 2048; i++)
	{
		memory[i].reset();//does not destroy the elements. only sets all bits to 0;
	}
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