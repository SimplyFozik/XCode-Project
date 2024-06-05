#include <iostream>
#include "Encrypt.h";
#include "Descrypt.h";

int main()
{
	std::string text;
	std::cin >> text;
	funcGenerateSeed(text);
}