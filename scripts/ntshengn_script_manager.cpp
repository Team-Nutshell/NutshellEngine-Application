// This file is automatically generated by generate_script_manager.py from CMake

#pragma once
#include "ntshengn_script_manager.h"

NtshEngn::Scriptable NtshEngn::ScriptManager::createScriptable(const std::string& scriptName) {
	NTSHENGN_UNUSED(scriptName);

	Scriptable scriptable;


	return scriptable;
}

extern "C" NTSHENGN_SCRIPT_MANAGER_API NtshEngn::ScriptManagerInterface* createScriptManager() {
	return new NtshEngn::ScriptManager;
}

extern "C" NTSHENGN_SCRIPT_MANAGER_API void destroyScriptManager(NtshEngn::ScriptManagerInterface* sm) {
	delete sm;
}