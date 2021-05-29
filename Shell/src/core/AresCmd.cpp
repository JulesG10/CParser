#include "AresCmd.h"
using namespace AresConsole;

AresCmd::AresCmd(AresLog* log, char* loc)
{
	this->log = log;
	AresCoreCmd* cmd = new AresCoreCmd(loc,log);
	AresFiles* files = new AresFiles(loc, log);
	AresPaint* paint = new AresPaint(loc, log);
	AresRequest* req = new AresRequest(loc, log);
	AresStorage* stor = new AresStorage(loc, log);

	this->commands.push_back(cmd);
	this->commands.push_back(files);
	this->commands.push_back(paint);
	this->commands.push_back(req);
	this->commands.push_back(stor);
}


AresCmd::~AresCmd()
{
	this->commands.clear();
}

bool AresCmd::execute(char* input)
{
	for (AresCommandObject* obj : commands)
	{
		if (obj->is_cmd(input))
		{
			obj->execute(input);
			return true;
			break;
		}
	}

	return false;
}