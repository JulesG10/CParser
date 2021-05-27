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
		std::cout << "[INFO] ";
		break;
	case AresConsole::L_ERROR:
		std::cout << "[ERROR] ";
		break;
	case AresConsole::L_FAIL:
		std::cout << "[FAIL] ";
		break;
	case AresConsole::L_WARM:
		std::cout << "[WARM] ";
		break;
	case AresConsole::L_SUCCESS:
		std::cout << "[SUCCESS] ";
		break;
	}
	std::cout << v << end;
	SetConsoleTextAttribute(console, (FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED));
}

void AresLog::color(int color)
{
	SetConsoleTextAttribute(console, color);
}

AresLog::~AresLog()
{
   
}