#pragma once
#include <string>

void charToint(int* intArr[], char* charArr[])
{
	int counter = 0;
	for (int i = 0; i < 145; i++)
		if (isdigit(*charArr[i]))
		{
			for (; isdigit(*charArr[i]); i++)
			{
				if (*intArr[counter] < 0)
				{
					*intArr[counter] = *charArr[i] - '0';
				}
				else
				{
					*intArr[counter] = (*intArr[counter] * 10) + (*charArr[i] - '0');
				}
			}
			i--;
			counter++;
		}
}