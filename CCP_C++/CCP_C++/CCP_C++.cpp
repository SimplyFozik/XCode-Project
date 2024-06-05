#include <iostream>
#include "Encrypt.h";
#include "Decrypt.h";

int main()
{
	std::string text;
	std::getline(std::cin, text);
	funcGenerateSeed(text);
}