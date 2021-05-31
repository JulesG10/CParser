#include "AresCoreCmd.h"
using namespace AresConsole;

#include <iostream>
#include <string>
#include <sstream>
#include <regex>
#include <vector>
#include <stdexcept>
#include <stdio.h>
#include "../AresIO.h"

AresCoreCmd::AresCoreCmd(char* loc, AresLog*& l)
{
	this->log = l;
	this->location = std::string(loc);
}

AresCoreCmd::~AresCoreCmd()
{

}

bool AresCoreCmd::is_cmd(char* input)
{
	std::string strinput(input);
	std::stringstream ssinput(strinput);
	std::string segment;
	std::vector<std::string> split;
	while (std::getline(ssinput, segment, ' '))
	{
		split.push_back(segment);
	}
	if (split.size() >= 1)
	{
		for (std::string& s : private_cmd)
		{
			if (s == split[0])
			{
				return false;
			}
		}

		AresIO* io = new AresIO();
		std::string exepath = location + "extensions\\" + split[0] + ".exe";
		if (io->exists((char*)exepath.c_str()))
		{
			return true;
		}

		delete io;
	}

	return false;
}

bool AresCoreCmd::execute(char* input)
{
	std::string strinput(input);
	std::stringstream ssinput(strinput);
	std::string segment;
	std::vector<std::string> split;
	while (std::getline(ssinput, segment, ' '))
	{
		split.push_back(segment);
	}
	if (split.size() >= 1)
	{
		std::string exepath = location + "extensions\\" + split[0] + ".exe";
		split.erase(split.begin());
		std::string exeargv;

		for (std::string& s : split)
		{
			exeargv += " " + s;
		}

		char buffer[128];
		std::string result = "";
		std::string cmd(exepath + " " + exeargv);
		FILE* pipe = _popen(std::string(exepath + exeargv).c_str(), "r");
		if (pipe)
		{
			try 
			{
				while (fgets(buffer, sizeof buffer, pipe) != NULL) {
					result += buffer;
				}
			}
			catch (...) 
			{
				_pclose(pipe);
				throw;
			}
			log->print(result.c_str(), L_NONE);
			_pclose(pipe);
		}else
		{
			log->print(std::string("Fail to execute " + cmd).c_str(), L_ERROR);
		}
		ShowWindow(GetForegroundWindow(), SW_SHOW);
	}
	return true;
}