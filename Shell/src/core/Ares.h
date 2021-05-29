#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include "../AresLog.h"
#include "../AresSetup.h"
#include "AresCmd.h"

namespace AresConsole
{
	class Ares
	{
	public:
		Ares(char**);
		~Ares();
		int start();
	private:
		AresSetup* setup;
		AresLog* log;
		AresCmd* cmd;
		char** argv;
	};
}


