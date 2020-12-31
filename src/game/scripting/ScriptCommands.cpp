#include "game\scripting\ScriptCommands.h"
#include "game\Scene.h"
#include "game\Entity.h"
#include "rendering\CRenderer.h"
#include "game\AnimatedEntity.h"

int ScriptCommands::MoveEntity(lua_State *L) {
	int n = lua_gettop(L);
	if (n != 3) {
		lua_error(L);
	}
	Entity *e = Scene::GetInstance()->GetEntity((unsigned) lua_tonumber(L, 1));
	if (e == NULL) {
		lua_error(L);
	}
	e->TranslateTo((float) lua_tonumber(L, 2), (float) lua_tonumber(L, 3));
	return 0;
}

int ScriptCommands::PrintText(lua_State *L) {
	int n = lua_gettop(L);
	if (n != 6) {
		lua_error(L);
	}
	CRenderer::GetInstance()->DrawText((unsigned) lua_tonumber(L, 1),
		(unsigned) lua_tonumber(L, 2),
		(unsigned) lua_tonumber(L, 3),
		(unsigned) lua_tonumber(L, 4),
		(unsigned) lua_tonumber(L, 5),
		(const char *) lua_tostring(L, 6));
	return 0;
}

int ScriptCommands::SpawnAnimated(lua_State *L) {
	int n = lua_gettop(L);
	if (n != 3) {
		lua_error(L);
	}
	lua_pushnumber(L, (lua_Number) Scene::GetInstance()->AddEntity(
		new AnimatedEntity(
				(unsigned) lua_tonumber(L, 1),
				(float) lua_tonumber(L, 2),
				(float) lua_tonumber(L, 3)))
		);
	return 0;
}

int ScriptCommands::RemoveEntity(lua_State *L) {
	int n = lua_gettop(L);
	if (n != 1) {
		lua_error(L);
	}
	Scene::GetInstance()->RemoveEntity((unsigned) lua_tonumber(L, 1));
	return 0;
}

void ScriptCommands::RegisterAll(lua_State *L) {
	lua_register(L, "move_entity", MoveEntity);
	lua_register(L, "print_text", PrintText);
	lua_register(L, "spawn_animated", SpawnAnimated);
	lua_register(L, "remove_entity", RemoveEntity);
}
