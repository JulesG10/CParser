#include "AresCoreCmd.h"
using namespace AresConsole;

#include <iostream>
#include <string>
#include <regex>

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
	std::regex input_match("(cmd)", std::regex_constants::ECMAScript | std::regex_constants::icase);
	if (std::regex_search(std::string(input), input_match))
	{
		return true;
	}
	return false;
}

bool AresCoreCmd::execute(char*)
{
	return true;
}