#include "AresFiles.h"
using namespace AresConsole;

#include<iostream>
#include<string>
#include <regex>

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
	std::regex input_match("(file)", std::regex_constants::ECMAScript | std::regex_constants::icase);
	if (std::regex_search(std::string(input), input_match))
	{
		return true;
	}
	return false;
}

bool AresFiles::execute(char*)
{
	return true;
}