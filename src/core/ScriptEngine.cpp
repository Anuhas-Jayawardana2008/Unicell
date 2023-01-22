#include "core/ScriptEngine.h"
#include "core/Scene.h"
#include <GLFW/glfw3.h>

namespace unicell
{
	int cpp_key_down(lua_State* L)
	{
		int key = lua_tointeger(L, 1);
		int state = glfwGetKey(glfwGetCurrentContext(), key) == GLFW_PRESS;
		lua_pushboolean(L, state);
		return 1;
	}

	int cpp_key_up(lua_State* L)
	{
		int key = lua_tointeger(L, 1);
		int state = glfwGetKey(glfwGetCurrentContext(), key) == GLFW_RELEASE;
		lua_pushboolean(L, state);
		return 1;
	}

	ScriptEngine::ScriptEngine(Scene* scene)
		:context(scene)
	{
	}

	ScriptEngine::~ScriptEngine()
	{
		this->context = nullptr;
	}

	void ScriptEngine::Initialize()
	{
		this->state = luaL_newstate();
		luaL_openlibs(this->state);
	}

	void ScriptEngine::RunFile(const std::string& file)
	{
		if (luaL_dofile(this->state, file.c_str()) != LUA_OK)
		{
			printf("%s\n", lua_tostring(this->state, -1));
		}
	}

	void ScriptEngine::LoadEngineUtils()
	{
		// transform
		lua_pushinteger(this->state, 0);
		lua_setglobal(this->state, "x");
		lua_pushinteger(this->state, 0);
		lua_setglobal(this->state, "y");

		// input mapping...
		lua_pushinteger(this->state, GLFW_KEY_W);
		lua_setglobal(this->state, "KEY_W");
		lua_pushinteger(this->state, GLFW_KEY_A);
		lua_setglobal(this->state, "KEY_A");
		lua_pushinteger(this->state, GLFW_KEY_S);
		lua_setglobal(this->state, "KEY_S");
		lua_pushinteger(this->state, GLFW_KEY_D);
		lua_setglobal(this->state, "KEY_D");

		// game table...
		lua_newtable(this->state);
		lua_pushglobaltable(this->state);
		lua_setglobal(this->state, "game");
	
		// input table..
		lua_newtable(this->state);
		lua_pushglobaltable(this->state);
		lua_setglobal(this->state, "Input");

		lua_getglobal(this->state, "Input");
		lua_pushcfunction(this->state, cpp_key_down);
		lua_setfield(this->state, -2, "getKeyDown");
	}

	void ScriptEngine::EditProperties(const entt::entity& entity)
	{
		auto& tc = this->context->GetRegistry().get<TransformComponent>(entity);
		lua_getglobal(this->state, "x");
		double x = lua_tonumber(this->state, -1);
		lua_pop(this->state, 1);

		lua_getglobal(this->state, "y");
		double y = lua_tonumber(this->state, -1);
		lua_pop(this->state, 1);

		tc.position.x = x;
		tc.position.y = y;
	}

	void ScriptEngine::Start(const entt::entity& entity)
	{
		auto& tc = this->context->GetRegistry().get<TransformComponent>(entity);

		lua_setglobal(this->state, "x");
		lua_getglobal(this->state, "game");
		lua_getfield(this->state, -1, "start");
		lua_pcall(this->state, 0, 0, 0);
	}

	void ScriptEngine::Update()
	{
		lua_getglobal(this->state, "game");
		lua_getfield(this->state, -1, "update");
		lua_pcall(this->state, 0, 0, 0);
	}

	void ScriptEngine::Close()
	{
		lua_close(this->state);
	}
}