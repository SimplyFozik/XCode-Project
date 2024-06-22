#pragma once
#include <string>

std::string getRecieverByCode(int index)
{
	switch (index)
	{
	case 1:
		return "C++";
		break;
	case 2:
		return "C#";
		break;
	case 3:
		return "Python";
		break;
	case 4:
		return "Java";
		break;
	case 5:
		return "Lua";
		break;
	default:
		return "Undefined";
		break;
	}
}