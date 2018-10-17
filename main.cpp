/*
Author: Cordell Hurst
Course: 340, Operating Systems
Instructor: Prof Pavel Shostak
Assignment: OperatingSystem/Memory Management Simulation
computer

*/
#include <string>
#include <iostream>
#include <limits>

#include "OS.h"
//#include "mainMemory.h"

using namespace std;

//constructor for simulated computer
void makeComputer(unsigned int &, unsigned int &, int &);//uns int memSizeIn, int pgSizeIn, int HDDquantity
void failCheckMain(istream &cin);

int main()
{
	cout << "\nAuthors: Cordell Hurst, Alex Bortoc and Johnny Zhu\nCourse: CSCI 360, Computer Architecture III"
		<< "\nInstructor: Xiaojie Zhang\nAssignment: "
		<< "Software Simulator/Multi-Level Memory Memory Hierarchy\n" << endl;

	OS MyOS;

	MyOS.switchGo();

	/* Initial testing

	Register* temp = MyCache.get_GeneralPurposeRegisters_GPRs();
	string mystring =
	temp->word.to_string<char, std::string::traits_type, std::string::allocator_type>();

	cout << "\n" << endl;
	for (int i = 0; i < 4; i++)
	{
	cout << i << " = " << temp[i].word << endl;
	bitset<1> temp2;
	temp[i].word.set(3);
	temp2[0] = temp[i].word[4];
	cout << i << " = " << temp[i].word << "     " << temp2 << endl;
	}
	char temp2;
	cout << "\nWaiting..." << endl;
	cin >> temp2;
	*/

	/*
	unsigned int memorySizeIn;
	unsigned int pageSizeIn;
	int numOfHDD;

	makeComputer(memorySizeIn, pageSizeIn, numOfHDD);

	HDD HDDArray(numOfHDD);
	main_memory memory_module(memorySizeIn, pageSizeIn);
	processor CPU;


	//info check
	cout << "Your computer::" << endl;
	memory_module.getMemoryInfo();
	HDDArray.printHardDrives();
	cout << "\n\nEnter '9' to terminate program." << endl;
	MyOS.switchGo(CPU, memory_module, HDDArray);
	*/
}
//catches failed input cast and resets istream
void failCheckMain(istream &cin)
{
	if (cin.fail())
	{
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
}
//Constructor for the computer
void makeComputer(unsigned int &memorySizeIn, unsigned int &pageSizeIn, int &numOfHDDIn)
{
	unsigned int check = 4000000000;
	do
	{
		failCheckMain(cin);

		cout << "How much DRAM do I have?" << endl;
		cin >> memorySizeIn;

		if (memorySizeIn < 1 || memorySizeIn > check)
			cout << " Memory Size must be greater than zero (0) and less than or equal to 4 "
			<< "billion bytes (4000000000). Do not enter commas or any other puntuation or letters." << endl;

	} while (cin.fail() || memorySizeIn < 1 || memorySizeIn > check);

	do
	{
		failCheckMain(cin);

		cout << "What is my page/frame size?" << endl;
		cin >> pageSizeIn;

	} while (cin.fail() || pageSizeIn < 1 || pageSizeIn > check);

	int HDDIn = 0;
	do
	{
		failCheckMain(cin);
		cout << "How many hard disks do I have?" << endl;
		cin >> HDDIn;
	} while (cin.fail() || HDDIn < 1);

	numOfHDDIn = HDDIn;
}
