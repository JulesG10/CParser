#include "AresPaint.h"
using namespace AresConsole;
#include<iostream>
#include<string>
#include <regex>

AresPaint::AresPaint(char* loc, AresLog*& l)
{
	this->log = l;
	this->location = std::string(loc);
}

AresPaint::~AresPaint()
{

}

bool AresPaint::is_cmd(char* input)
{
	std::regex input_match("(paint)", std::regex_constants::ECMAScript | std::regex_constants::icase);
	if (std::regex_search(std::string(input), input_match))
	{
		return true;
	}
	return false;
}

bool AresPaint::execute(char*)
{
	return true;
}