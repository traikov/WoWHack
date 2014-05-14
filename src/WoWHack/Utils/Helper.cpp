#pragma once

#include "Helper.h"

std::string Helper::GetDllDir()
{
	std::string dllName = "WoWHack!GUIMain.dll";
	char path[MAX_PATH];
	GetModuleFileNameA(GetModuleHandleA(dllName.c_str()), path, MAX_PATH);
	std::string dir = path;
	int start = dir.rfind("\\");
	dir.erase(dir.begin() + start + 1, dir.end());

	return dir;
}