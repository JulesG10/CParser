#pragma once
#include "AresCommandObject.h"
#include "../AresLog.h"
namespace AresConsole
{
	class AresPaint : public AresCommandObject
	{
	public:
		AresPaint(char*, AresLog*&);
		~AresPaint();
		bool execute(char*) override;
		bool is_cmd(char*) override;
	private:
		std::string location;
		AresLog* log;
	};
}
