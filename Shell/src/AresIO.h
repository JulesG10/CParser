#pragma once
#include<iostream>
#include<Windows.h>
#include<Shlwapi.h>

namespace AresConsole 
{
	enum IOCodes
	{
		FAIL,
		SUCCESS,
		EXISTS,
		NO_FOUND
	};

	class AresIO
	{
	public:
		AresIO();
		~AresIO();

		IOCodes file_exists(char*);
		IOCodes file_remove(char*);
		
		IOCodes folder_exists(char*);
		IOCodes folder_remove();

		bool exists(char*);
	};
}

