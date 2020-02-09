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
	cout << GetInitialTimeStamp() << endl;

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

	// Do-while loop to send and receive data
	char buf[4096];
	string userInput;

	LogMessage a;	
	a.DisplayDate();
	while (1)
	{
		// Prompt the user for some text
		this_time = clock() / CLOCKS_PER_SEC;

	if (_kbhit())
	{
		cout << "Enter an input: " << endl;
		userInput = _getch();
		cout << "You entered: " << userInput << endl;
	
		if (userInput.size() > 0)		// Make sure the user has typed in something
		{
			// Send the text
			int sendResult = send(sock, userInput.c_str(), userInput.size() + 1, 0);

			LogMessage(0, userInput[0]);

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
		//cout << this_time << endl;
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
					cout << "SERVER> " << string(buf, 0, bytesReceived) << endl;
					bytesReceived = 0;
					ZeroMemory(buf, 4096);
				}
			}
		}

	} //while (userInput.size() > 0);

	// Gracefully close down everything
	closesocket(sock);
	WSACleanup();

}