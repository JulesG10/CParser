#include "AresSetup.h"
using namespace AresConsole;

AresSetup::AresSetup(AresLog*& log)
{
	this->log = log;
	this->io = new AresIO();
}

void AresSetup::start(char* l_path)
{
	this->set_location(l_path);
	log->print("Checking Ares files and folders...");
	this->verify_files();

}

void AresSetup::set_location(char* loc)
{
	std::stringstream location(loc);
	std::vector<std::string> split;
	std::string segment;
	while (std::getline(location, segment, '\\'))
	{
		split.push_back(segment);
	}
	split.pop_back();

	std::string final_loc = "";
	for (std::string el : split)
	{
		final_loc += el + "\\";
	}
	this->location_path = (char*)malloc(final_loc.size());
	strcpy(this->location_path, final_loc.c_str());
	split.clear();

	std::string msg = "Get evironement location ";
	msg += std::string(this->location_path);
	this->log->print(msg.c_str());
}

void AresSetup::verify_files()
{
	std::string path(this->location_path);
	for (const char* folder : this->folders)
	{
		if (!this->io->exists((char*)(path + std::string(folder)).c_str()))
		{
			std::string err = "Folder \'";
			err += (path + std::string(folder));
			err += "\' no found";
			log->print(err.c_str(), LogTypes::L_WARM);

			IOCodes c = this->io->folder_exists((char*)(path + std::string(folder)).c_str());
			if (c == IOCodes::SUCCESS)
			{
				log->print("New folder created", LogTypes::L_SUCCESS);
			}else
			{
				log->print("Fail to create folder", LogTypes::L_ERROR);
			}
		}
	}
}


AresSetup::~AresSetup()
{
	delete this->io;
}