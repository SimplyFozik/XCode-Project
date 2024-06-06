#include <iostream>
#include <winsock2.h>
#include <stdlib.h>
#include <thread>
#include <chrono>
#include <Encrypt.h>
#include <Decrypt.h>
#pragma comment(lib,"ws2_32.lib")
#pragma warning(disable: 4996)

void funcSendMessage(SOCKET newConnection,std::string text)
{
	text = "";
	std::getline(std::cin, text);
	send(newConnection, funcGenerateSeed(text).c_str(), sizeof(text), NULL);
	funcSendMessage(newConnection,text);
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
		std::string text;
		std::thread th1(funcSendMessage,newConnection,text);
		std::thread th2(funcWaitForAnwser,newConnection);
	}

	system("pause");
	return 0;

	/*std::string text = "ANUUH WHOUS!";
	int seed[26]{ 11,4,16,23,21,25,6,0,13,9,20,15,19,1,7,2,10,14,3,12,17,5,22,24,18,8 };
	funcDecrypt(seed,text);
	std::getline(std::cin, text);
	funcGenerateSeed(text);
	ANUUH WHOUS!*/
}