#pragma once
#include <ctime>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <utility>

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
		if (index < 52)
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
	char def_alph[52]{ 'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z','a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z' };
	char new_alph[52]{ 'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z','a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z' };
	std::string enc_text = "";
	for (int i = 0; i < 51; i++)
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

std::pair<std::string,std::string> funcGenerateSeed(std::string text)
{
	srand(time(0));
	int seed[52]{ 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51 };
	std::random_shuffle(&seed[0], &seed[52]);
	std::string seedString;
	for (int i = 0; i < 52; i++)
	{
		seedString += tostr(seed[i]) + ',';
		std::cout << seed[i];
	}
	return std::make_pair(funcEncrypt(seed,text),seedString);
}	