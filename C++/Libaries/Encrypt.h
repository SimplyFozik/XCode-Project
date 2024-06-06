#pragma once
#include <ctime>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>

template <typename T> std::string tostr(const T& t)
{
	std::ostringstream os;
	os << t;
	return os.str();
}

int funcGetIndexEncrypt(char letter,char new_alph[])
{
	int index = 0;
	while (letter != new_alph[index])
	{
		if (index < 26)
		{
			index++;
		}
		else
		{
			return -1; // there is no such symbol
		}
	}
	return index;
}

std::string funcEncrypt(int seed[],std::string text)
{
	char def_alph[26]{ 'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z' };
	char new_alph[26]{ 'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z' };
	std::string enc_text = "";
	for (int i = 0; i < 26; i++)
	{
		char buffer = new_alph[i];
		new_alph[i] = new_alph[seed[i]];
		new_alph[seed[i]] = buffer;
	}
	for (int i = 0; i < text.size(); i++)
	{
		if (std::isalpha(text[i]))
		{
			enc_text += def_alph[funcGetIndexEncrypt(text[i], new_alph)];
		}
		else
		{
			enc_text += text[i];
		}
	}
	return enc_text;
}

std::string funcGenerateSeed(std::string text)
{
	srand(time(0));
	int seed[26]{0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25};
	std::random_shuffle(&seed[0], &seed[26]);
	for (int i = 0; i < 26; i++)
	{
		std::cout << seed[i] << " ";
	}
	std::cout << std::endl;
	return funcEncrypt(seed,text);
}	