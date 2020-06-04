#include "LogMessage.h"


LogMessage::LogMessage() 
{
	SetInput('0');
	timeStamp = GetActualTimeStamp();
}

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

void GetTime(int *hour, int *min, int *sec)
{
	struct tm newtime;
	time_t now = time(0);
	localtime_s(&newtime, &now);

	*hour = newtime.tm_hour;
	*min = newtime.tm_min;
	*sec = newtime.tm_sec;
}


void WriteLog(string fileName, LogMessage log)
{
	ofstream ofs(fileName, ios::app);
	ofs << log;
	ofs.close();
}

int HowManyShots(string message)
{
	int t_index;
	int shots;
	for (int i = 0; i < message.size(); i++)
	{
		if (message[i] == 't')
		{
			t_index = i;
		}
	}
	if (t_index == 2)
	{
		shots = (int)message[1] - 48;
	}
	else if (t_index == 3)
	{
		shots = ((int)message[1]-48) * 10 + ((int)message[2]-48);
	}
	else if (t_index == 4)
	{
		shots = ((int)message[1]-48) * 100 + ((int)message[2]-48) * 10 + ((int)message[3]-48);
	}

	return shots;
}

int HowManyTargetsHit(string message)
{
	int t_index, targetSize;
	int targets;
	for (int i = 0; i < message.size(); i++)
	{
		if (message[i] == 't')
		{
			t_index = i;
		}
	}

	targetSize = message.size() - t_index - 1;

	if (targetSize == 1)
	{
		targets = (int)message[t_index+1] - 48;
	}
	else if (targetSize == 2)
	{
		targets = (((int)message[t_index + 1] - 48) * 10) + ((int)message[t_index + 2] - 48);
	}
	else if (targetSize == 3)
	{
		targets = ((((int)message[t_index + 3] - 48) * 100) + ((int)message[t_index + 2] - 48) * 10) + ((int)message[t_index + 3] - 48);
	}
	return targets;
}