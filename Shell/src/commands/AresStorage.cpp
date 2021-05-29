#include "AresStorage.h"
using namespace AresConsole;


AresStorage::AresStorage(char* loc, AresLog*& l)
{
	this->log = l;
	this->location = std::string(loc);

	if (sqlite3_open(std::string(location + "data\\local.db").c_str(),&db))
	{
		std::string fail = "Fail to open local database: ";
		fail += sqlite3_errmsg(db);
		this->log->print(fail.c_str(), LogTypes::L_ERROR);
	}else
	{
		this->log->print("Open local database", LogTypes::L_SUCCESS);
		this->execute_sqlite3("CREATE TABLE IF NOT EXISTS storage (data VARCHAR)");
	}
}

AresStorage::~AresStorage()
{
	sqlite3_close(db);
}

bool AresStorage::is_cmd(char* input)
{
	std::regex input_match("(storage)\s* (add|find|del|clear|help|list)\s* ?([a-zA-Z0-9])*");
	if (std::regex_search(std::string(input), input_match))
	{
		return true;
	}
	return false;
}

static int db_callback(void* NotUsed, int argc, char** argv, char** azColName)
{
	int i;
	for (i = 0; i < argc; i++)
	{
		std::cout << "[" << i << "] " /* << azColName[i] << " = "*/ << (argv[i] ? argv[i] : "NULL") << std::endl;
	}
	return 0;
}

bool AresStorage::execute(char* input)
{
	std::string strinput(input);
	std::stringstream ssinput(strinput);
	std::string segment;
	std::vector<std::string> split;
	while (std::getline(ssinput, segment, ' '))
	{
		split.push_back(segment);
	}
	if (split.size() >= 2)
	{
		std::string action = split[1];
		std::string msg = "Storage Object execute command " + action;
		log->print(msg.c_str());

		std::string req;
		if (action == "add" && split.size() >= 3)
		{
			req = "INSERT INTO storage(data) VALUES('"+split[2]+"')";
		}else if(action == "find" && split.size() >= 3)
		{
			req = "SELECT * FROM storage WHERE data LIKE '" + split[2] + "'";
		}
		else if (action == "del" && split.size() >= 3)
		{
			req = "DELETE FROM storage WHERE data = '" + split[2] + "'";
		}
		else if (action == "clear")
		{
			req = "DELETE FROM storage";
		}
		else if (action == "help")
		{
			this->log->print("[USAGE] storage (add|del|clear|find|list|help) <data>", L_NONE);
		}
		else if (action == "list")
		{
			req = "SELECT * FROM storage";
		}

		this->execute_sqlite3(req);
	}

	return true;
}

void AresStorage::execute_sqlite3(std::string req)
{
	char* zErrMsg = 0;
	if (sqlite3_exec(db, req.c_str(), db_callback, 0, &zErrMsg) != SQLITE_OK)
	{
		std::string fail = "Database error: ";
		fail += sqlite3_errmsg(db);
		this->log->print(fail.c_str(), LogTypes::L_ERROR);
		sqlite3_free(zErrMsg);
	}
}