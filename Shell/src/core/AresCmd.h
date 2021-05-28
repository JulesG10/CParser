#pragma once
#include<iostream>
#include<vector>
#include "../commands/AresCommandObject.h"

namespace AresConsole
{
	class AresCmd
	{
	public:
		AresCmd();
		~AresCmd();
		bool execute(char*);
	private:
		std::vector<AresCommandObject> commands;
	};
}
