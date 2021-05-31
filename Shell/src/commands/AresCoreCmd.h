#pragma once
#include "AresCommandObject.h"
#include "../AresLog.h"
namespace AresConsole
{
	class AresCoreCmd : public AresCommandObject
	{
	public:
		AresCoreCmd(char*, AresLog*&);
		~AresCoreCmd();
		bool execute( char*) override;
		bool is_cmd(char*) override;
	private:
		std::string location;
		AresLog* log;

		std::string private_cmd[6] = { "folder","file","paint","req","request","storage" };
	};
}

