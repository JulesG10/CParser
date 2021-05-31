#include "AresLog.h"
using namespace AresConsole;



AresLog::AresLog()
{
	console = GetStdHandle(STD_OUTPUT_HANDLE);
}

void AresLog::print(const char* v, LogTypes type, char end)
{
	switch (type)
	{
	case AresConsole::L_INFO:
		this->color(Blue, Black);
		std::cout << "[INFO] ";
		this->color(White, Black);
		break;
	case AresConsole::L_ERROR:
		this->color(Red, Black);
		std::cout << "[ERROR] ";
		this->color(White, Black);
		break;
	case AresConsole::L_FAIL:
		this->color(LightYellow, Black);
		std::cout << "[FAIL] ";
		this->color(White, Black);
		break;
	case AresConsole::L_WARM:
		this->color(Yellow, Black);
		std::cout << "[WARM] ";
		this->color(White, Black);
		break;
	case AresConsole::L_SUCCESS:
		this->color(Green, Black);
		std::cout << "[SUCCESS] ";
		this->color(White, Black);
		break;
	}
	std::cout << v << end;
	
	this->color(White,Black);
}

void AresLog::color(ColorTypes forground, ColorTypes background)
{
	SetConsoleTextAttribute(console, ((int)background * 16) + (int)forground);
}

AresLog::~AresLog()
{
   
}