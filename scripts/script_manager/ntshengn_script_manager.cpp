// This file is automatically generated by generate_script_manager.py from CMake

#include "ntshengn_script_manager.h"

#include "../GamepadTestScript.h"

NtshEngn::Scriptable NtshEngn::ScriptManager::createScriptable(const std::string& scriptName) {
	Scriptable scriptable;

	if (scriptName == "GamepadTestScript") {
		GamepadTestScript* script = createScript<GamepadTestScript>();
		script->createEditableScriptVariableMap();
		scriptable.script = script;
	}

	return scriptable;
}

void GamepadTestScript::createEditableScriptVariableMap() {
}

extern "C" NTSHENGN_SCRIPT_MANAGER_API NtshEngn::ScriptManagerInterface* createScriptManager() {
	return new NtshEngn::ScriptManager;
}

extern "C" NTSHENGN_SCRIPT_MANAGER_API void destroyScriptManager(NtshEngn::ScriptManagerInterface* sm) {
	delete sm;
}