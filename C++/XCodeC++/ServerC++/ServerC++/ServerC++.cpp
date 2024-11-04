#include <iostream>
#include <winsock2.h>
#include <stdlib.h>
#include <thread>
#include <chrono>
#include <Encrypt.h>
#include <Decrypt.h>
#include <Shared.h>
#pragma comment(lib,"ws2_32.lib")
#pragma warning(disable: 4996)

SOCKET Connections[100];
int Counter = 0;
const unsigned short index = 1;

unsigned short Cpp_Connectons[100]; // 1
unsigned short Cpp_TopConnection = 0;

unsigned short Cs_Connections[100]; // 2
unsigned short Cs_TopConnections = 0;

unsigned short Py_Connections[100]; // 3
unsigned short Py_TopConnection = 0;

unsigned short Java_Connections[100]; // 4
unsigned short Java_TopConnections = 0;

unsigned short Lua_Connections[100]; // 5
unsigned short Lua_TopConnections = 0;


void funcSendMessage(int index)
{
	while (true)
	{
		std::string text;
		std::getline(std::cin, text);

		int msg_size = text.size();
		std::pair<std::string, std::string> result = funcGenerateSeed(text);

		send(Connections[index], (char*)&msg_size, sizeof(int), NULL);
		send(Connections[index], result.first.c_str(), msg_size, NULL);
		Sleep(10);
		send(Connections[index], result.second.c_str(), 145, NULL);
		Sleep(10);
	}
}


void funcWaitForAnwser(SOCKET Connection)
{
	while (true)
	{
		unsigned short msg_size = 0;
		unsigned short Recieved = recv(Connection, (char*)&msg_size, sizeof(int), NULL);

		if (Recieved <= 0)
		{
			system("cls");
			std::cout << "Error #1\n" << "No Bytes Recieved.\n";
			exit(1);
		}

		char* msg = new char[msg_size + 1];

		Recieved = recv(Connection, msg, msg_size, NULL);

		if (Recieved <= 0)
		{
			delete[] msg;
			std::cout << "Error #2\n" << "Failed To Get Message.\n";
			exit(2);
		}

		msg[Recieved] = '\0'; // Null Termination.

		char seed[146] = { 0 };
		Recieved = recv(Connection, seed, 145, NULL);

		if (Recieved <= 0)
		{
			delete[] msg;
			std::cout << "Error #3\n" << "Failed To Get Seed.\n";
			exit(3);
		}

		unsigned short counter = 0;
		int intseed[52] = { 0 }; // Initialize the array

		for (unsigned short i = 0; i < 145; i++) // Convert Char array to Int array
		{
			if (isdigit(seed[i]))
			{
				for (; isdigit(seed[i]); i++)
				{
					intseed[counter] = (intseed[counter] * 10) + (seed[i] - '0');
				}
				i--;
				counter++;
			}
		}

		std::string decryptedMessage = funcDecrypt(intseed, msg);
		std::cout << decryptedMessage << std::endl;

		// Clear variables.
		delete[] msg;
	}
}



int main(int argc, char* argv[])
{
	//WSAStartup
	WSAData wsaData;
	WORD DLLVersion = MAKEWORD(2, 1);
	if (WSAStartup(DLLVersion, &wsaData) != 0)
	{
		std::cout << "Error\n";
		exit(1);
	}
	SOCKADDR_IN addr;
	int sizeofaddr = sizeof(addr);
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	addr.sin_port = htons(1111);
	addr.sin_family = AF_INET;

	SOCKET sListen = socket(AF_INET, SOCK_STREAM, NULL);
	bind(sListen, (SOCKADDR*)&addr, sizeof(addr));
	listen(sListen, SOMAXCONN);

	SOCKET newConnection;
	for (int i = 0; i < 100; i++)
	{
		newConnection = accept(sListen, (SOCKADDR*)&addr, &sizeofaddr);


		if (newConnection == 0)
		{
			std::cout << "Error #2\n";
		}
		else
		{
			Connections[i] = newConnection;

			int connection_index = 0;
			recv(Connections[i], (char*)&connection_index, sizeof(int), NULL);

			Counter++;

			switch (index)
			{
			case 1:
				std::cout << '#' << Cpp_TopConnection << " C++ client connected!\n";
				Cpp_Connectons[Cpp_TopConnection] = Counter;
				Cpp_TopConnection++;
				break;
			case 2:
				std::cout << '#' << Cs_TopConnections << " C# client connected!\n";
				Cs_Connections[Cs_TopConnections] = Counter;
				Cs_TopConnections++;
				break;
			case 3:
				std::cout << '#' << Py_TopConnection << " Python client connected!\n";
				Py_Connections[Py_TopConnection] = Counter;
				Py_TopConnection++;
				break;
			case 4:
				std::cout << '#' << Java_TopConnections << " Java client connected!\n";
				Java_Connections[Java_TopConnections] = Counter;
				Java_TopConnections++;
				break;
			case 5:
				std::cout << '#' << Lua_TopConnections << " Lua client connected!\n";
				Lua_Connections[Lua_TopConnections] = Counter;
				Lua_TopConnections++;
				break;
			}


			// MultiThreading
			//CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)funcWaitForAnwser, (LPVOID)(i), NULL, NULL);
			//CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)funcSendMessage, (LPVOID)(i), NULL, NULL);
		}
	}

	system("pause");
	return 0;
}

// Press [F] Fozik.