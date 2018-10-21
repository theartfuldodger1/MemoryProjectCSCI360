/*
Author: Cordell Hurst, Alex BOrtoc, Johnny Zhu
Course: CSCI 360, Computer Architecture III
Instructor: Xiaojie Zhang
Assignment: Memory Management Simulation
This program...
*/
#include <string>
#include <iostream>
#include <limits>

#include "OS.h"

using namespace std;

void failCheckMain(istream &cin);

int main()
{
	cout << "\nAuthors: Cordell Hurst, Alex Bortoc and Johnny Zhu\nCourse: CSCI 360, Computer Architecture III"
		<< "\nInstructor: Xiaojie Zhang\nAssignment: "
		<< "Software Simulator/Multi-Level Memory Memory Hierarchy\n" << endl;

	OS MyOS;

	MyOS.switchGo();

	return 0;
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