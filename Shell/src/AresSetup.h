#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <Windows.h>

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
		
		bool is_admin();
		bool request_admin();
	private:
		char* location_path;
		void verify_files();
		void remove_files();
		
		void try_admin();
		

		bool isAdmin = false;

		void set_location(char*);

		AresLog* log;
		AresIO* io;

		std::vector<const char*> folders =
		{
			"data",
			"backups",
			"extensions",
			"temp",
			"settings",
			"data\\images",
			"data\\files"
		};

		std::vector<const char*> files =
		{
			"data\\web.json",
			"data\\shell.json",
			"data\\local.db",
			"settings\\extensions.json",
			"settings\\preferences.json"
		};
	};
}


