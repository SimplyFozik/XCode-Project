#include <iostream>
#include <winsock2.h>
#include <stdlib.h>
#include <thread>
#include <chrono>
#include <Encrypt.h>
#include <Decrypt.h>
#pragma comment(lib,"ws2_32.lib")
#pragma warning(disable: 4996)

void funcSendMessage(SOCKET newConnection, std::string text)
{
	std::getline(std::cin, text);
	int msg_size = text.size();
	send(newConnection, (char*)&msg_size, sizeof(int), NULL);
	send(newConnection, funcGenerateSeed(text).c_str(), msg_size, NULL);
	funcSendMessage(newConnection, text);
}

void funcWaitForAnwser(SOCKET Connection, std::string text)
{
	int msg_size;
	std::string msg;
	for (;;)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
		recv(Connection, (char*)&msg_size, sizeof(int), NULL);
		char* msg = new char[msg_size + 1];
		msg[msg_size] = '\0';
		recv(Connection, msg, msg_size, NULL);
		std::cout << msg << std::endl;
		delete[] msg;
	}

}

//void funcCheckConnection(SOCKET Connection)
//{
//	if (Connection == 1)
//	{
//		std::this_thread::sleep_for(std::chrono::milliseconds(1));
//		exit(1);
//	}
//	else
//	{
//		funcCheckConnection(Connection);
//	}
//}

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
		std::thread th2(funcWaitForAnwser, Connection,text);
		/*std::thread th3(funcCheckConnection, Connection);*/
		th1.join();
		th2.join();
		/*th3.join();*/
	}
	
}
