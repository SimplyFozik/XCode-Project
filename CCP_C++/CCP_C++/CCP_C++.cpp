#include <iostream>
#include "Encrypt.h";
#include "Decrypt.h";

int main()
{
	std::string text;
	//int seed[26]{ 24, 2, 11, 20, 19, 21, 0, 4, 12, 9, 3, 22, 7, 14, 18, 25, 16, 5, 23, 17, 6, 1, 13, 15, 8, 10 };
	//funcDecrypt(seed,text);
	std::getline(std::cin, text);
	funcGenerateSeed(text);
}