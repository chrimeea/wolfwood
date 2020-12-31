#include "game\scripting\ScriptManager.h"
#include "utils\Config.h"
#include <string.h>
#include "game\scripting\ScriptCommands.h"
#include "utils\Config.h"

ScriptManager *ScriptManager::instance = NULL;

ScriptManager::ScriptManager()
{
	unsigned int k = 0;
    scripts = new std::vector<std::string>();
	char *fileName = Config::GetValue("config/scripts/scriptsfile");
	if (fileName) {
		Config::ReadMappingsV(fileName, scripts);
	}
	char *s = Config::GetValue("config/scripts/scriptsDir");
	baseDir = (char *) malloc((strlen(s) + 1) * sizeof(char *));
	strcpy(baseDir, s);
	L = lua_open();
	ScriptCommands::RegisterAll(L);
}

ScriptManager::~ScriptManager()
{
	lua_close(L);
	if (scripts != NULL) delete scripts;
	free(baseDir);
}

void ScriptManager::Close()
{
	if (instance != NULL) {
		delete instance;
	}
}

ScriptManager *ScriptManager::GetInstance()
{
	if (instance == NULL) {
		instance = new ScriptManager();
	}
	return instance;
}

void ScriptManager::RunScript(unsigned scriptId)
{
	std::string m = (*scripts)[scriptId];
	char *s = (char *) malloc((strlen(baseDir) + m.size() + 1) * sizeof(char));
	strcpy(s, baseDir);
	strcat(s, m.c_str());
	lua_dofile(L, s);
	free(s);
}

int ScriptManager::RunCommand(const char *comm)
{
	return lua_dostring(L, comm);
}