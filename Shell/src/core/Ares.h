#pragma onçce
#include "../AresLog.h"
#include "../AresSetup.h"
namespace AresConsole
{
	class Ares
	{
	public:
		Ares();
		~Ares();
		int start();
	private:
		AresSetup setup;
		AresLog log;
	};
}


