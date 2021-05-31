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
	ShowWindow(GetForegroundWindow(), SW_SHOW);
	this->setup->start(this->argv[0]);

	char* location = new char[MAX_PATH];
	strcpy(location,this->setup->get_location());
	this->cmd = new AresCmd(this->log, location);

	while (true)
	{
		log->print(">", L_NONE, ' ');
		std::string line;
		std::getline(std::cin, line);

		this->cmd->execute((char*)line.c_str());
	}
	return 0;
}

Ares::~Ares()
{
	delete this->cmd;
	delete this->log;
	delete this->setup;
}