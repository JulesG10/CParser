#include "AresSetup.h"
using namespace AresConsole;

AresSetup::AresSetup(AresLog*& log)
{
	this->log = log;
}

void AresSetup::start()
{
	log->print("Checking ares files and folders...");
	this->verify_files();
}

void AresSetup::verify_files()
{

}


AresSetup::~AresSetup()
{

}