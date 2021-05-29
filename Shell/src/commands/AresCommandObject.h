#pragma once
#include "../AresLog.h"
namespace AresConsole
{
	class AresCommandObject
	{
	public:
		virtual bool execute(char*);
		virtual bool is_cmd(char*);
	};
}

