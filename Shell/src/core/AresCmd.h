#pragma once
#include<iostream>
#include<vector>
#include "../commands/AresCommandObject.h"
#include "../commands/AresCoreCmd.h"
#include "../commands/AresFiles.h"
#include "../commands/AresPaint.h"
#include "../commands/AresRequest.h"
#include "../commands/AresStorage.h"
#include "../AresLog.h"

namespace AresConsole
{
	class AresCmd
	{
	public:
		AresCmd(AresLog* log,char* loc);
		~AresCmd();
		bool execute(char*);
	private:
		std::vector<AresCommandObject*> commands = {};
		AresLog* log;
	};
}
