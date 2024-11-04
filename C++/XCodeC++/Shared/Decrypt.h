#pragma once

int funcGetIndexDecrypt(char letter, char def_alph[])
{
	unsigned short index = 0;
	while (letter != def_alph[index])
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

std::string funcDecrypt(int seed[], std::string text)
{
	char def_alph[52]{ 'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z','a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z' };
	char new_alph[52]{ 'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z','a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z' };
	std::string enc_text = "";
	for (unsigned short i = 0; i < 52; i++)
	{
		char buffer = new_alph[i];
		new_alph[i] = new_alph[seed[i]];
		new_alph[seed[i]] = buffer;
	}
	for (unsigned short i = 0; i < text.size(); i++)
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
	return enc_text;
}