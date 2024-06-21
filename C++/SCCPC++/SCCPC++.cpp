#include <iostream>
#include <winsock2.h>
#include <stdlib.h>
#include <thread>
#include <chrono>
#include <Encrypt.h>
#include <Decrypt.h>
#pragma comment(lib,"ws2_32.lib")
#pragma warning(disable: 4996)

void funcSendMessage(SOCKET newConnection)
{
	while (true)
	{	
		std::string text;
		std::getline(std::cin, text);
		
		int msg_size = text.size();
		std::pair<std::string, std::string> result = funcGenerateSeed(text);
		
		send(newConnection, (char*)&msg_size, sizeof(int), NULL);
		send(newConnection, result.first.c_str(), msg_size, NULL);
		Sleep(10);
		send(newConnection, result.second.c_str(), 145, NULL);
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
		
		char seed[146] = {0};
		Recieved = recv(Connection, seed, 145, NULL);

		if (Recieved <= 0)
		{
			delete[] msg;
			std::cout << "Error #3\n" << "Failed To Get Seed.\n";
			exit(3);
		}
		
		unsigned short counter = 0;
		int intseed[52] = {0}; // Initialize the array
		
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
	newConnection = accept(sListen, (SOCKADDR*)&addr, &sizeofaddr);

	if (newConnection == 0)
	{
		std::cout << "Error #2\n";
	}
	else
	{
		std::cout << "Client Connection - OK.\n";
		std::thread th1(funcSendMessage,newConnection);
		std::thread th2(funcWaitForAnwser,newConnection);
		/*std::thread th3(funcCheckConnection, newConnection);*/
		th1.join();
		th2.join();
		/*th3.join();*/
	}

	WSACleanup();
	system("pause");
	return 0;
}