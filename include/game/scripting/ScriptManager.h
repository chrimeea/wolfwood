#ifndef SCRIPTMANAGER
#define SCRIPTMANAGER

extern "C"
{
#include "game\scripting\lua\lauxlib.h"
}

#include "utils\Config.h"

#define LUA_EXT .luac

class ScriptManager
{
private:
	char *baseDir;
	lua_State *L;
	std::vector<std::string> *scripts;
	unsigned int total;
	static ScriptManager *instance;
	ScriptManager();
	~ScriptManager();
public:
	static ScriptManager *GetInstance();
	static void Close();
	void RunScript(unsigned);
	int RunCommand(const char *);
};

#endif