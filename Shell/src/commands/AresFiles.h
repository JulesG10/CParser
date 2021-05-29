#pragma once
#include "AresCommandObject.h"
#include "../AresLog.h"
namespace AresConsole
{
	class AresFiles : public AresCommandObject
	{
	public:
		AresFiles(char*, AresLog*&);
		~AresFiles();
		bool execute(char*) override;
		bool is_cmd(char*) override;
	private:
		std::string location;
		AresLog* log;
	};
}
