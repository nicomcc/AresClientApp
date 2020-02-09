#include "LogMessage.h"

LogMessage::LogMessage(char input, int hour)
{
	SetInput(input);
	SetTime(hour);
}

void LogMessage::SetInput(char s)
{
	input = s;
}

void LogMessage::SetTime(int t)
{
	hour = t;
}

void LogMessage::WriteMessage()
{

}


std::ofstream & operator<<(std::ofstream &ofs, LogMessage &a)
{
	ofs << a.hour << std::endl;
	ofs << a.input << std::endl;
	return ofs;
}

std::ifstream & operator>>(std::ifstream &ifs, LogMessage &a)
{
	ifs >> a.hour >> a.input;
	return ifs;
}

std::ostream & operator<<(std::ostream &os, LogMessage &a)
{
	os << "Horario: " << a.hour << std::endl;
	os << "Comando: " << a.input << std::endl;
	return os;
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