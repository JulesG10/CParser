#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<vector>
#include <sstream>
#include<string>
#include "AresLog.h"
#include "AresIO.h"

namespace AresConsole
{
	class AresSetup
	{
	public:
		AresSetup(AresLog*&);
		~AresSetup();
		void start(char*);
	private:
		char* location_path;
		void verify_files();
		int setup_files();
		void remove_files();
		bool request_admin();

		void set_location(char*);

		AresLog* log;
		AresIO* io;

		std::vector<const char*> folders =
		{
			"data",
			"backups",
			"extensions",
			"temp",
		};
	};
}


