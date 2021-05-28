#pragma once
namespace AresConsole
{
	class AresCommandObject
	{
	public:
		AresCommandObject();
		~AresCommandObject();

		bool execute(char*);
		bool is_cmd(char*);
	};
}

