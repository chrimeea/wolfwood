#ifndef SCRIPTCOMMANDS_H
#define SCRIPTCOMAMNDS_H

extern "C"
{
#include "game\scripting\lua\lauxlib.h"
}

class ScriptCommands {
public:
	static int MoveEntity(lua_State *);
	static int PrintText(lua_State *);
	static int SpawnAnimated(lua_State *);
	static int RemoveEntity(lua_State *);
	static void RegisterAll(lua_State *);
};

#endif
