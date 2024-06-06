#pragma once
#include <iostream>

int funcGetIndexDecrypt(char letter, char def_alph[])
{
	int index = 0;
	while (letter != def_alph[index])
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

void funcDecrypt(int seed[], std::string text)
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
			enc_text += new_alph[funcGetIndexDecrypt(text[i], def_alph)];	
		}
		else
		{
			enc_text += text[i];
		}
	}
	std::cout << enc_text;
}