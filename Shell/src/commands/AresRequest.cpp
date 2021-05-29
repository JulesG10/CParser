#include "AresRequest.h"
using namespace AresConsole;

AresRequest::AresRequest(char* loc, AresLog*& l)
{
	this->log = l;
	this->location = std::string(loc);
}

AresRequest::~AresRequest()
{

}

bool AresRequest::is_cmd(char* input)
{
	std::regex input_match("(req|request)\s* (print|download|header|help)\s* ?(http:\/\/www\.|https:\/\/www\.|http:\/\/|https:\/\/)[a-z0-9]+([\-\.]{1}[a-z0-9]+)*\.[a-z]{2,5}(:[0-9]{1,5})?(\/.*)", std::regex_constants::ECMAScript | std::regex_constants::icase);
	if (std::regex_search(std::string(input), input_match))
	{
		return true;
	}
	return false;
}

bool AresRequest::execute(char* input)
{
	std::string strinput(input);
	std::stringstream ssinput(strinput);
	std::string segment;
	std::vector<std::string> split;
	while (std::getline(ssinput, segment, ' '))
	{
		split.push_back(segment);
	}

	return true;
}