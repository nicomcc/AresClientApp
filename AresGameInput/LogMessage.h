
#include <string>
#include <fstream>
#include <iostream>
#include <ctime>
#include <sstream>

using namespace std;

#ifndef LOGMESSAGE_H
#define LOGMESSAGE_H




class LogMessage
{
private:
	char input;
	int hour;
	

public:
	LogMessage() {}
	LogMessage(char input, int hour);
	char GetInput() { return input; }
	int GetTime() { return hour; }

	void SetInput(char s);
	void SetTime(int t);


	void DisplayDate()
	{
		struct tm newtime;
		time_t now = time(0);
		localtime_s(&newtime, &now);
		std::cout << (newtime.tm_year + 1900) << '-'
			<< (newtime.tm_mon + 1) << '-'
			<< newtime.tm_mday << '-'
			<< newtime.tm_hour << ':' << newtime.tm_min <<"\n";
	}

	void WriteMessage();

	friend std::ofstream & operator<<(std::ofstream &ofs, LogMessage &a);
	friend std::ifstream & operator>>(std::ifstream &ifs, LogMessage &a);
	friend std::ostream & operator<<(std::ostream &os, LogMessage &a);


	~LogMessage() {}

};

std::string IntToString(int a);

//get initial timestamp for file name
std::string GetInitialTimeStamp();


#endif // LOGMESSAGE_H

