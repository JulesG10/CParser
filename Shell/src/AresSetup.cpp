#include "AresSetup.h"
using namespace AresConsole;

AresSetup::AresSetup(AresLog*& log)
{
	this->log = log;
	this->io = new AresIO();
	this->isAdmin = this->is_admin();
}

void AresSetup::start(char* l_path)
{
	this->set_location(l_path);
	log->print("Checking Ares files and folders...");
	this->verify_files();
	log->print("Files and folders ok.");
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

bool AresSetup::is_admin()
{
	BOOL fIsRunAsAdmin = FALSE;
	DWORD dwError = ERROR_SUCCESS;
	PSID pAdministratorsGroup = NULL;
	SID_IDENTIFIER_AUTHORITY NtAuthority = SECURITY_NT_AUTHORITY;
	if (!AllocateAndInitializeSid(
		&NtAuthority,
		2,
		SECURITY_BUILTIN_DOMAIN_RID,
		DOMAIN_ALIAS_RID_ADMINS,
		0, 0, 0, 0, 0, 0,
		&pAdministratorsGroup))
	{
		dwError = GetLastError();
		goto Cleanup;
	}
	if (!CheckTokenMembership(NULL, pAdministratorsGroup, &fIsRunAsAdmin))
	{
		dwError = GetLastError();
		goto Cleanup;
	}

Cleanup:
	if (pAdministratorsGroup)
	{
		FreeSid(pAdministratorsGroup);
		pAdministratorsGroup = NULL;
	}
	if (ERROR_SUCCESS != dwError)
	{
		throw dwError;
	}

	return fIsRunAsAdmin;
}

bool AresSetup::request_admin()
{
	wchar_t szPath[MAX_PATH];
	if (GetModuleFileName(NULL, szPath, ARRAYSIZE(szPath)))
	{
		SHELLEXECUTEINFO sei = { sizeof(sei) };
		sei.lpVerb = L"runas";
		sei.lpFile = szPath;
		sei.hwnd = NULL;
		sei.nShow = SW_NORMAL;
		if (!ShellExecuteEx(&sei))
		{
			DWORD dwError = GetLastError();
			if (dwError == ERROR_CANCELLED)
			{
				log->print(" You did not allow admin elevation, exit.", L_ERROR);
			}
		}else
		{
			exit(0);
			return true;
		}
	}
	return false;
}

void AresSetup::try_admin()
{
	if (!this->isAdmin)
	{
		log->print("Try with admin privileges.");
		if (this->request_admin())
		{
			log->print("Fail to get admin privileges, exit.", L_ERROR);
		}else
		{
			log->print("Success to get admin privileges", L_SUCCESS);
		}
	}
}

void AresSetup::remove_files()
{
	std::string path(this->location_path);

	for (const char* folder : this->folders)
	{
		char* combine = new char[(path + std::string(folder)).size()];
		strcpy(combine, (path + std::string(folder)).c_str());

		if (!this->io->exists(combine))
		{
			if (io->folder_remove(combine) == SUCCESS)
			{
				std::string msg = "Remove folder \'";
				msg += std::string(combine);
				msg += "\'";
				log->print(msg.c_str(),LogTypes::L_SUCCESS);
			}else
			{
				std::string msg = "Fail to remove folder \'";
				msg += std::string(combine);
				msg += "\'";
				log->print(msg.c_str(), LogTypes::L_WARM);
				this->try_admin();
				this->remove_files();
				break;
			}
		}
	}

	for (const char* file : this->files)
	{
		char* combine = new char[(path + std::string(file)).size()];
		strcpy(combine, (path + std::string(file)).c_str());

		if (!this->io->exists(combine))
		{
			if (io->file_remove(combine) == SUCCESS)
			{
				std::string msg = "Remove file \'";
				msg += std::string(combine);
				msg += "\'";
				log->print(msg.c_str(), LogTypes::L_SUCCESS);
			}
			else
			{
				std::string msg = "Fail to file folder \'";
				msg += std::string(combine);
				msg += "\'";
				log->print(msg.c_str(), LogTypes::L_WARM);
				this->try_admin();
				this->remove_files();
				break;
			}
		}
	}
}

void AresSetup::verify_files()
{
	std::string path(this->location_path);

	for (const char* folder : this->folders)
	{
		char* combine = new char[(path + std::string(folder)).size()];
		strcpy(combine, (path + std::string(folder)).c_str());

		if (!this->io->exists(combine))
		{
			std::string err = "Folder \'";
			err += std::string(combine);
			err += "\' no found";
			IOCodes c = this->io->folder_exists(combine);
			if (c == IOCodes::SUCCESS)
			{
				log->print("New folder created", LogTypes::L_SUCCESS);
			}else
			{
				log->print("Fail to create folder", LogTypes::L_ERROR);
				this->try_admin();
				this->verify_files();
				break;
			}
		}
	}

	for (const char* file : this->files)
	{
		char* combine = new char[(path + std::string(file)).size()];
		strcpy(combine, (path + std::string(file)).c_str());

		
		if (!this->io->exists(combine))
		{
			std::string err = "File \'";
			err += std::string(combine);
			err += "\' no found";
			log->print(err.c_str(), LogTypes::L_WARM);

			IOCodes c = this->io->file_exists(combine);
			if (c == IOCodes::SUCCESS)
			{
				log->print("New file created", LogTypes::L_SUCCESS);
			}
			else
			{
				log->print("Fail to create file", LogTypes::L_ERROR);
				this->try_admin();
				this->verify_files();
				break;
			}
		}
	}
}


AresSetup::~AresSetup()
{
	delete this->io;
}