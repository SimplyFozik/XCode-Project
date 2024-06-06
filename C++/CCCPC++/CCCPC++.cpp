#include <iostream>
#include <winsock2.h>
#include <stdlib.h>
#include <thread>
#include <chrono>
#include <Encrypt.h>
#include <Decrypt.h>
#pragma comment(lib,"ws2_32.lib")
#pragma warning(disable: 4996)

void funcSendMessage(SOCKET Connection, std::string text)
{
	text = "";
	std::getline(std::cin, text);
	send(Connection, funcGenerateSeed(text).c_str(), sizeof(text), NULL);
	funcSendMessage(Connection, text);
}

void funcWaitForAnwser(SOCKET Connection)
{
	char msg[256];
	for (;;)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
		recv(Connection, msg, sizeof(msg), NULL);
		std::cout << msg << std::endl;
	}
}

int main(int argc, char* argv[])
{
	//WSAStartup
	WSAData wsaData;
	WORD DLLVersion = MAKEWORD(2, 1);
	if (WSAStartup(DLLVersion, &wsaData) != 0)
	{
		std::cout << "Error" << std::endl;
		exit(1);
	}
	SOCKADDR_IN addr;
	int sizeofaddr = sizeof(addr);
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	addr.sin_port = htons(1111);
	addr.sin_family = AF_INET;

	SOCKET Connection = socket(AF_INET, SOCK_STREAM, NULL);
	if (connect(Connection, (SOCKADDR*)&addr, sizeof(addr)) != 0)
	{
		std::cout << "Error: failed connect to server.\n";
		return 1;
	}
	else
	{
		std::cout << "Server Connection - OK\n";
		std::string text;
		std::thread th1(funcSendMessage, Connection, text);
		std::thread th2(funcWaitForAnwser, Connection);
	}
	
}
