#pragma once

#include "..\WoWHack.h"

namespace ConsoleCommands
{
	void Install();
	BOOL __cdecl CCommand_LanguageHack(char const* cmd, char const* args);
	BOOL __cdecl CCommand_GoToCorpse(char const* cmd, char const* args);
	BOOL __cdecl CCommand_FlyHack(char const* cmd, char const* args);
	BOOL __cdecl CCommand_LevitateHack(char const* cmd, char const* args);
	BOOL __cdecl CCommand_FreezeZHack(char const* cmd, char const* args);
	BOOL __cdecl CCommand_ClimbHack(char const* cmd, char const* args);
	BOOL __cdecl CCommand_MorphHack(char const* cmd, char const* args);
	BOOL __cdecl CCommand_ChangeScaleHack(char const* cmd, char const* args);
	BOOL __cdecl CCommand_SpectateModeHack(char const* cmd, char const* args);
}