#include "AresRequest.h"
using namespace AresConsole;

AresRequest::AresRequest(char* loc, AresLog*& l)
{
	this->log = l;
	this->location = std::string(loc);
	RestClient::init();
}

AresRequest::~AresRequest()
{
	RestClient::disable();
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
	if (split.size() >= 2)
	{
		std::string action = split[1];
		std::string msg = "Request Object execute command " + action;
		log->print(msg.c_str());

		if (action == "print" && split.size() >= 3)
		{
			std::string msg = "\n" + RestClient::get(split[2]).body + "\n";
			log->print(msg.c_str(), L_NONE);
		}else if(action == "download" && split.size() >= 3)
		{
			std::string path = this->location + "data\\downloads\\"+std::to_string(time(NULL))+".txt";
			std::ofstream data(path);
			if (data.good())
			{
				data << RestClient::get(split[2]).body;
				this->log->print(std::string("Create file " + path).c_str(), L_SUCCESS);
				data.close();
			}else
			{
				log->print(std::string("Fail to create file " + path).c_str(), L_ERROR);
			}
		}
		else if (action == "header" && split.size() >= 3)
		{
			for (auto header : RestClient::get(split[2]).headers)
			{
				log->print(std::string(header.first + " " + header.second).c_str(), L_NONE);
			}
		}
		else if (action == "help")
		{
			this->log->print("[USAGE] (req|request) (print|download|header|help) <url>", L_NONE);
		}
		else
		{
			std::string msg = "Command '" + action + "' not found";
			log->print(msg.c_str());
		}
	}
	split.clear();
	return true;
}