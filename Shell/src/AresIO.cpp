#include "AresIO.h"
using namespace AresConsole;

AresIO::AresIO()
{

}

IOCodes AresIO::file_exists(char* file)
{
	IOCodes c = IOCodes::EXISTS;
	if (!this->exists(file))
	{
		wchar_t wfile[MAX_PATH];
		mbstowcs(wfile, file, MAX_PATH);
		HANDLE handle = CreateFile(wfile, GENERIC_ALL, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		if (!handle)
		{
			c = IOCodes::FAIL;
		}else
		{
			c = IOCodes::SUCCESS;
		}
		delete wfile;
	}

	return c;
}

IOCodes AresIO::file_remove(char* file)
{
	if (!this->exists(file))
	{
		return IOCodes::NO_FOUND;
	}

	wchar_t wfile[MAX_PATH];
	mbstowcs(wfile, file, MAX_PATH);
	if (DeleteFile(wfile))
	{
		return IOCodes::SUCCESS;
	}
	delete wfile;

	return IOCodes::FAIL;
}

IOCodes AresIO::folder_exists(char* folder)
{
	if (!this->exists(folder))
	{
		wchar_t wfolder[MAX_PATH];
		mbstowcs(wfolder, folder, MAX_PATH);
		LPSECURITY_ATTRIBUTES lpSecurityAttr = {};
		if (!CreateDirectory(wfolder, lpSecurityAttr))
		{
			return IOCodes::FAIL;
		}else
		{
			return IOCodes::SUCCESS;
		}
		delete wfolder;
	}

	return IOCodes::EXISTS;
}

IOCodes AresIO::folder_remove(char* folder)
{
	if (!this->exists(folder))
	{
		return IOCodes::NO_FOUND;
	}

	wchar_t wfolder[MAX_PATH];
	mbstowcs(wfolder, folder, MAX_PATH);
	if (RemoveDirectory(wfolder))
	{
		return IOCodes::SUCCESS;
	}
	delete wfolder;
	return IOCodes::FAIL;
}

bool AresIO::exists(char* path)
{
	DWORD typ = GetFileAttributesA(path);
	if (typ == INVALID_FILE_ATTRIBUTES)
	{
		return false;
	}
	else if (typ & FILE_ATTRIBUTE_DIRECTORY)
	{
		return true;
	}

	return false;
}

AresIO::~AresIO()
{

}