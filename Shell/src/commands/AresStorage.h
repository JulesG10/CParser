#pragma once
#include "AresCommandObject.h"
#include "../AresLog.h"

#include<sqlite3.h>
#include <iostream>
#include <string>
#include <sstream>
#include <regex>
#include <vector>

namespace AresConsole
{
	class AresStorage : public AresCommandObject
	{
	public:
		AresStorage(char*, AresLog*&);
		~AresStorage();
		bool execute(char*) override;
		bool is_cmd(char*) override;
	private:
		void execute_sqlite3(std::string req);
		std::string location;
		sqlite3* db;
		AresLog* log;
	};
}
