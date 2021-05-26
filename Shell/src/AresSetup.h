#pragma once
#include<iostream>
#include<vector>
#include "AresLog.h"

namespace AresConsole
{
	class AresSetup
	{
	public:
		AresSetup(AresLog*&);
		~AresSetup();
		void start();
	private:
		void verify_files();
		int setup_files();
		void remove_files();
		bool request_admin();
		AresLog* log;

		std::vector<const char*> folders =
		{
			"data",
			"backups",
			"extensions",
			"temp",
			""
		};
	};
}


