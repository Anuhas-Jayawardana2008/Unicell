#pragma once

#include "lua.hpp"
#include "entt.hpp"
#include <string>

namespace unicell
{
	class Scene;
	class ScriptEngine
	{
	public:
		ScriptEngine(Scene* scene);
		~ScriptEngine();

		void RunFile(const std::string& file);

		void EditProperties(const entt::entity& entity);

		void Initialize();
		void LoadEngineUtils();

		void Start(const entt::entity& entity);
		void Update();

		void Close();
	private:
		Scene* context = nullptr;
		lua_State* state = nullptr;
	};
}