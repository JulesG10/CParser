#pragma once
#include "AresCommandObject.h"
#include "../AresLog.h"
#include <iostream>
#include <string>
#include <sstream>
#include <regex>
#include <vector>
#include <fstream>
#include<restclient-cpp/restclient.h>

namespace AresConsole
{
	class AresRequest : public AresCommandObject
	{
	public:
		AresRequest(char*, AresLog*&);
		  ~AresRequest();
		bool execute(char*) override;
		bool is_cmd(char*) override;
	private:
		std::string location;
		AresLog* log;
	};
}

