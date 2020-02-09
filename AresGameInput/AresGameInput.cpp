#include <iostream>
#include <string>
#include <WS2tcpip.h>
#include <conio.h>
#include <time.h>
#include <fstream>
#include "LogMessage.h"

#pragma comment(lib, "ws2_32.lib")

using namespace std;

void main()
{
	bool connection = false;
	string messageReceived = "";

	//Get log file name
	string fileName = GetInitialTimeStamp();

	string ipAddress = "127.0.0.1";			// IP Address of the server
	int port = 8052;

	clock_t this_time = 0;
	clock_t last_time = 0;

	// Initialize WinSock
	WSAData data;
	WORD ver = MAKEWORD(2, 2);
	int wsResult = WSAStartup(ver, &data);
	if (wsResult != 0)
	{
		cerr << "Can't start Winsock, Err #" << wsResult << endl;
		return;
	}

	// Create socket
	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == INVALID_SOCKET)
	{
		cerr << "Can't create socket, Err #" << WSAGetLastError() << endl;
		WSACleanup();
		return;
	}

	// Fill in a hint structure
	sockaddr_in hint;
	hint.sin_family = AF_INET;
	hint.sin_port = htons(port);
	inet_pton(AF_INET, ipAddress.c_str(), &hint.sin_addr);

	// Connect to server
	int connResult = connect(sock, (sockaddr*)&hint, sizeof(hint));
	if (connResult == SOCKET_ERROR)
	{
		cerr << "Can't connect to server, Err #" << WSAGetLastError() << endl;
		closesocket(sock);
		WSACleanup();
		return;
	}

	//while loop to send and receive data
	char buf[4096];
	string userInput;

	cout << "waiting for server connection" << endl;

	while (1)
	{
	
	this_time = clock() / CLOCKS_PER_SEC;

	if (messageReceived[0] == 's' && !connection)
	{
		cout << "Connected to Server! Hit 'b' to begin!" << endl;
		connection = true;
	}
	//check if any key was pressed (prevents program from hang on getch()
	if (_kbhit())
	{
		cout << "Enter an input: " << endl;
		userInput = _getch();
		// Send text if input is valid
		if (CheckValidInput(userInput[0]))
		{
			cout << "You entered: " << userInput << endl;
	
			if (userInput.size() > 0)		// Make sure the user has typed in something
			{
					int sendResult = send(sock, userInput.c_str(), userInput.size() + 1, 0);
					
					LogMessage log(userInput[0]);
					//operator overload to print object
					cout << log << endl;
					//write log on file 
					ofstream ofs(fileName, ios::app);
					ofs << log;
					ofs.close();

					if (sendResult != SOCKET_ERROR)
					{
						// Wait for response
						ZeroMemory(buf, 4096);
						int bytesReceived = recv(sock, buf, 4096, 0);
						if (bytesReceived > 0)
						{
							// Echo response to console
							cout << "SERVER> " << string(buf, 0, bytesReceived) << endl;
							bytesReceived = 0;
							ZeroMemory(buf, 4096);
						}
					}
				}
			}
		else 
			cout << "Invalid Input!" << endl; //if CheckValidInput(userInput[0]) returns false:

	}

	//keep sending status request to server
		if (this_time != last_time)
		{
			last_time = this_time;
			
			int sendResult = send(sock, "0", userInput.size() + 1, 0);
			if (sendResult != SOCKET_ERROR)
			{
				// Wait for response
				ZeroMemory(buf, 4096);
				int bytesReceived = recv(sock, buf, 4096, 0);
				if (bytesReceived > 0)
				{
					// Echo response to console
					messageReceived = string(buf, 0, bytesReceived);
					cout << "SERVER> " << string(buf, 0, bytesReceived) << endl;
					bytesReceived = 0;
					ZeroMemory(buf, 4096);
				}
			}
		}

	} 

	//close down everything
	closesocket(sock);
	WSACleanup();

}