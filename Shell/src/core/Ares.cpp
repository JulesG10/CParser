#include "Ares.h"
using namespace AresConsole;

Ares::Ares(char** args)
{
	this->log =  new AresLog();
	this->setup = new AresSetup(this->log);

	this->argv = (char**)malloc(sizeof(args));
	this->argv = args;
}

int Ares::start()
{
	this->setup->start(this->argv[0]);
	while (true)
	{
		log->print(">", L_NONE, ' ');
		std::string line;
		std::getline(std::cin, line);
		if (line == "exit")
		{
			break;
		}
	}
	return 0;
}

Ares::~Ares()
{
	delete this->log;
	delete this->setup;
}