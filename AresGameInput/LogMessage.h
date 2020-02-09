
#include <string>
#include <fstream>
#include <iostream>
#include <ctime>
#include <sstream>
#include <vector>

using namespace std;

#ifndef LOGMESSAGE_H
#define LOGMESSAGE_H




class LogMessage
{
private:
	char input;
	string timeStamp;
	

public:
	LogMessage() {}
	LogMessage(char input);

	char GetInput() { return input; }
	string GetTimeStamp() { return timeStamp; }

	void SetInput(char s);

	friend std::ofstream & operator<<(std::ofstream &ofs, LogMessage &a);
	friend std::ifstream & operator>>(std::ifstream &ifs, LogMessage &a);
	friend std::ostream & operator<<(std::ostream &os, LogMessage &a);


	~LogMessage() {}

};

bool CheckValidInput(char a);

std::string IntToString(int a);

//get initial timestamp for file name
std::string GetInitialTimeStamp();

std::string GetActualTimeStamp();


#endif // LOGMESSAGE_H

