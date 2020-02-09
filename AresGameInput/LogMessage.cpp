#include "LogMessage.h"

LogMessage::LogMessage(char input)
{
	SetInput(input);
	timeStamp = GetActualTimeStamp();
}

void LogMessage::SetInput(char s)
{
	if(CheckValidInput(s))
			input = s;
}

std::ofstream & operator<<(std::ofstream &ofs, LogMessage &a)
{
	ofs << a.timeStamp << std::endl;
	if(a.input != ' ')
		ofs << a.input << std::endl;
	else
		ofs << "SPACE" << std::endl;
	return ofs;
}

std::ifstream & operator>>(std::ifstream &ifs, LogMessage &a)
{
	ifs >> a.timeStamp >> a.input;
	return ifs;
}

std::ostream & operator<<(std::ostream &os, LogMessage &a)
{
	os << a.timeStamp << " Input: " << a.input << std::endl;
	return os;
}

bool CheckValidInput(char a)
{	
	vector <char> validInput = { 'a', 's', 'd', 'w', 'j', 'k', 'l', 'i', 'c', 'b', 'm', ' '};
	for (char i : validInput)
		if (a == i)
			return true;
}

string IntToString(int a)
{
	ostringstream temp;
	temp << a;
	return temp.str();
}

string GetInitialTimeStamp()
{
	struct tm newtime;
	time_t now = time(0);
	localtime_s(&newtime, &now);

	return (IntToString(newtime.tm_year + 1900) + '_' + IntToString(newtime.tm_mon + 1) + '_' +
		IntToString(newtime.tm_mday) + '_' + IntToString(newtime.tm_hour) + '_' + IntToString(newtime.tm_min) + ".txt");
	
}

string GetActualTimeStamp()
{
	struct tm newtime;
	time_t now = time(0);
	localtime_s(&newtime, &now);

	return (IntToString(newtime.tm_year + 1900) + '/' + IntToString(newtime.tm_mon + 1) + '/' +
		IntToString(newtime.tm_mday) + ' ' + IntToString(newtime.tm_hour) + ':' + IntToString(newtime.tm_min) + ":" + IntToString(newtime.tm_sec));

}