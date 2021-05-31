#include "AresFiles.h"
using namespace AresConsole;

#include <iostream>
#include <string>
#include <sstream>
#include <regex>
#include <vector>
#include "../AresIO.h"

AresFiles::AresFiles(char* loc, AresLog*& l)
{
	this->log = l;
	this->location = std::string(loc);
}

AresFiles::~AresFiles()
{

}

bool AresFiles::is_cmd(char* input)
{
	std::regex input_match("(file|folder)\s* (remove|create|exists)\s* <name>", std::regex_constants::ECMAScript | std::regex_constants::icase);
	if (std::regex_search(std::string(input), input_match))
	{
		return true;
	}
	return false;
}

bool AresFiles::execute(char* input)
{
	AresIO* io = new AresIO();
	std::string strinput(input);
	std::stringstream ssinput(strinput);
	std::string segment;
	std::vector<std::string> split;
	while (std::getline(ssinput, segment, ' '))
	{
		split.push_back(segment);
	}

	if (split.size() >= 3)
	{
		std::string action = split[1];
		std::string msg = split[0] + " Object execute command " + action;
		log->print(msg.c_str());

		std::vector<std::string> tmp = split;
		tmp.erase(tmp.begin() + 1);
		tmp.erase(tmp.begin() + 1);

		std::string arg = "";
		for (const std::string& part : tmp)
		{
			arg += part;
		}
		tmp.clear();

		if (split[0] == "file")
		{
			if (action == "remove")
			{
				IOCodes c = io->file_remove((char*)arg.c_str());
				switch (c)
				{
				case AresConsole::FAIL:
					log->print(std::string("Remove " + arg).c_str(), L_FAIL);
					break;
				case AresConsole::SUCCESS:
					log->print(std::string("Remove " + arg).c_str(), L_SUCCESS);
					break;
				case AresConsole::NO_FOUND:
					log->print(std::string("Not found " + arg).c_str(), L_ERROR);
					break;
				}
			}
			else if (action == "create")
			{
				IOCodes c = io->file_exists((char*)arg.c_str());
				switch (c)
				{
				case AresConsole::FAIL:
					log->print(std::string("Remove " + arg).c_str(), L_FAIL);
					break;
				case AresConsole::SUCCESS:
					log->print(std::string("Remove " + arg).c_str(), L_SUCCESS);
					break;
				case AresConsole::EXISTS:
					log->print(std::string("Already exists " + arg).c_str(), L_ERROR);
					break;
				}
			}
		}
		else
		{
			if (action == "remove")
			{
				IOCodes c = io->folder_remove((char*)arg.c_str());
				switch (c)
				{
				case AresConsole::FAIL:
					log->print(std::string("Remove " + arg).c_str(), L_FAIL);
					break;
				case AresConsole::SUCCESS:
					log->print(std::string("Remove " + arg).c_str(), L_SUCCESS);
					break;
				case AresConsole::NO_FOUND:
					log->print(std::string("Not found " + arg).c_str(), L_ERROR);
					break;
				}
			}
			else if (action == "create")
			{
				IOCodes c = io->folder_exists((char*)arg.c_str());
				switch (c)
				{
				case AresConsole::FAIL:
					log->print(std::string("Remove " + arg).c_str(), L_FAIL);
					break;
				case AresConsole::SUCCESS:
					log->print(std::string("Remove " + arg).c_str(), L_SUCCESS);
					break;
				case AresConsole::EXISTS:
					log->print(std::string("Already exists " + arg).c_str(), L_ERROR);
					break;
				}
			}
		}
		split.clear();

		if (action == "exists")
		{
			if (io->exists((char*)arg.c_str())) 
			{
				log->print(std::string("The " + split[0] + "  '" + arg + "' exist").c_str());
			}else
			{
				log->print(std::string("The " + split[0] + "  '" + arg + "' is not found").c_str());
			}
		}
	}

	delete io;
	return true;
}