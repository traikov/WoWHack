#pragma once

#include "..\WoWHack.h"

#include <vector>
#include <sstream>
#include <algorithm>

void ConsoleCommands::Install()
{
	WoWConsole::Get()->CommandRegister("LanguageHack", CCommand_LanguageHack, WoWConsole::ConsoleCmdGroup::Debug, nullptr);
	WoWConsole::Get()->CommandRegister("FlyHack", CCommand_FlyHack, WoWConsole::ConsoleCmdGroup::Debug, nullptr);
	WoWConsole::Get()->CommandRegister("LevitateHack", CCommand_LevitateHack, WoWConsole::ConsoleCmdGroup::Debug, nullptr);
	WoWConsole::Get()->CommandRegister("GoToCorpse", CCommand_GoToCorpse, WoWConsole::ConsoleCmdGroup::Debug, nullptr);
	WoWConsole::Get()->CommandRegister("FreezeZ", CCommand_FreezeZHack, WoWConsole::ConsoleCmdGroup::Debug, nullptr);
	WoWConsole::Get()->CommandRegister("ClimbHack", CCommand_ClimbHack, WoWConsole::ConsoleCmdGroup::Debug, nullptr);
	WoWConsole::Get()->CommandRegister("Morph", CCommand_MorphHack, WoWConsole::ConsoleCmdGroup::Debug, nullptr);
	WoWConsole::Get()->CommandRegister("ChangeScale", CCommand_ChangeScaleHack, WoWConsole::ConsoleCmdGroup::Debug, nullptr);
	WoWConsole::Get()->CommandRegister("SpectateMode", CCommand_SpectateModeHack, WoWConsole::ConsoleCmdGroup::Debug, nullptr);
}

BOOL __cdecl ConsoleCommands::CCommand_LanguageHack(char const* cmd, char const* args)
{
	int state = _strnicmp(args, "off", INT_MAX) != 0;

	byte LanguageHackOriginal[] = { 0x72, 0x11, 0x8B, 0x55, 0x18, 0x52, 0x56, 0x53, 0xE8, 0x74 };
	byte LanguageHackPatch[] = { 0x90, 0x90, 0x8B, 0x55 };
					 	
	if (state)
	{
		InternalMemory::WriteProtectedMemory(0x0050599F, LanguageHackPatch, 4);
		WoWLua::FrameScript_Execute::Get()->ExecuteCommand("DEFAULT_CHAT_FRAME:AddMessage(\"Language hack enabled.\");");
	}
	else
	{
		InternalMemory::WriteProtectedMemory(0x0050599F, LanguageHackOriginal, 10);
		WoWLua::FrameScript_Execute::Get()->ExecuteCommand("DEFAULT_CHAT_FRAME:AddMessage(\"Language hack disabled.\");");
	}
	
	return TRUE;
}

BOOL __cdecl ConsoleCommands::CCommand_GoToCorpse(char const* cmd, char const* args)
{
	float corpseXPos = *reinterpret_cast<float*>(corpse_Pos_X);
	float corpseYPos = *reinterpret_cast<float*>(corpse_Pos_Y);
	float corpseZPos = *reinterpret_cast<float*>(corpse_Pos_Z);

	if(corpseXPos != 0 && corpseYPos != 0 && corpseZPos != 0)
	{
		*reinterpret_cast<float*>(WoW::GetPlayer() + obj_Pos_X) = corpseXPos;
		*reinterpret_cast<float*>(WoW::GetPlayer() + obj_Pos_Y) = corpseYPos;
		*reinterpret_cast<float*>(WoW::GetPlayer() + obj_Pos_Z) = corpseZPos;		
	}
	else
	{
		WoWLua::FrameScript_Execute::Get()->ExecuteCommand("DEFAULT_CHAT_FRAME:AddMessage(\"Corpse not found !\");");
	}

	return TRUE;
}

BOOL __cdecl ConsoleCommands::CCommand_FlyHack(char const* cmd, char const* args)
{
	int state = _strnicmp(args, "off", INT_MAX) != 0;

	*reinterpret_cast<int*>(WoW::GetPlayer() + 0x7CF) = state ? 2 : 128;
	
	char msg[128];
	sprintf_s(msg, "DEFAULT_CHAT_FRAME:AddMessage(\"FlyHack %s.\");", args);
	WoWLua::FrameScript_Execute::Get()->ExecuteCommand(msg);

	return TRUE;
}

BOOL __cdecl ConsoleCommands::CCommand_LevitateHack(char const* cmd, char const* args)
{
	int state = _strnicmp(args, "off", INT_MAX) != 0;

	*reinterpret_cast<int*>(WoW::GetPlayer() + 0x7CF) = state ? 224 : 128;
	
	char msg[128];
	sprintf_s(msg, "DEFAULT_CHAT_FRAME:AddMessage(\"LevitateHack %s.\");", args);
	WoWLua::FrameScript_Execute::Get()->ExecuteCommand(msg);

	return TRUE;
}

///////////////////////////////////////////////////////////////////////////////////////
BOOL __cdecl ConsoleCommands::CCommand_FreezeZHack(char const* cmd, char const* args)
{
	int state = _strnicmp(args, "off", INT_MAX) != 0;
	//int on_off = -2147482624  -2147483648 }
	int freezeZ = state ? 0xFFFFFFFF80000400 : 0xFFFFFFFF80000000;
	InternalMemory::WriteProtectedMemory(WoW::GetPlayer() + 0x7CC, &freezeZ, sizeof(freezeZ));
	//int on_off[] = { -2147482624, -2147483648 };
					 
	char msg[128];
	sprintf_s(msg, "DEFAULT_CHAT_FRAME:AddMessage(\"FreezeZ %s.\");", args);
	WoWLua::FrameScript_Execute::Get()->ExecuteCommand(msg);

	return TRUE;
}

BOOL __cdecl ConsoleCommands::CCommand_ClimbHack(char const* cmd, char const* args)
{
	int state = _strnicmp(args, "off", INT_MAX) != 0;

	 *reinterpret_cast<float*>(WoW::GetPlayer() + game_SuperWallClimb) = state ? 255.F : 1.F;
	
	char msg[128];
	sprintf_s(msg, "DEFAULT_CHAT_FRAME:AddMessage(\"ClimbHack %s.\");", args);
	WoWLua::FrameScript_Execute::Get()->ExecuteCommand(msg);

	return TRUE;
}

BOOL __cdecl ConsoleCommands::CCommand_MorphHack(char const* cmd, char const* args)
{
	/*if(!args)
	{
		MessageBoxA(nullptr, "!args", "", 0);
		return TRUE;
	}
	*/
	//MessageBoxA(nullptr, args, "args", 0);

    std::istringstream iss(args);
	std::vector<std::string> vArgs;
	std::copy(std::istream_iterator<std::string>(iss),
         std::istream_iterator<std::string>(),
         std::back_inserter<std::vector<std::string> >(vArgs));
	
	if(vArgs.size() != 2)
		return TRUE;
		//MessageBoxA(nullptr, args, "args != 2", 0);

	//try
	{
		int morphID = atoi(vArgs.at(1).c_str());
		unsigned int Unit = WoW::GetTarget() ? WoW::GetTarget() : WoW::GetPlayer();

		char msg[128];
		if(vArgs.at(0).compare("unit") == 0)
		{
			MorphHack::Get()->MorphUnit(Unit, morphID);
			sprintf_s(msg, "DEFAULT_CHAT_FRAME:AddMessage(\"Morphed [%s] into %d\");", WoW::GetName(Unit), morphID);
		}
		else // if(vArgs.at(0) == "mount")
		{
			MorphHack::Get()->MorphMount(Unit, morphID);
			sprintf_s(msg, "DEFAULT_CHAT_FRAME:AddMessage(\"Morphed [%s]'s mount into %d\");", WoW::GetName(Unit), morphID);
		}
		WoWLua::FrameScript_Execute::Get()->ExecuteCommand(msg);
	}
	/*catch(const std::exception& oor) 
	{
		MessageBoxA(nullptr, oor.what(),"Exception", 0);
	}*/

	return TRUE;
}

BOOL __cdecl ConsoleCommands::CCommand_ChangeScaleHack(char const* cmd, char const* args)
{
	int scale = atoi(args);
	unsigned int Unit = WoW::GetTarget() ? WoW::GetTarget() : WoW::GetPlayer();
	*reinterpret_cast<float*>(Unit + ObjectScale) = static_cast<float>(scale);

	return TRUE;
}


BOOL __cdecl ConsoleCommands:: CCommand_SpectateModeHack(char const* cmd, char const* args)
{
	int state_On = _strnicmp(args, "on", INT_MAX) == 0;
	int stete_Off = _strnicmp(args, "off", INT_MAX) == 0;
	int state_Teleport = _strnicmp(args, "teleport", INT_MAX) == 0;
	// int state_Speed = _strnicmp(args, "speed", INT_MAX) == 0;

	unsigned char spectate_mod[] = {0, 0xFF};
	unsigned int Unit = WoW::GetPlayer();

	unsigned int spectator_base = *reinterpret_cast<unsigned int*>(Unit + 0x1008);

	if(state_On)
	{
		InternalMemory::WriteProtectedMemory(spectator_base + 0x0A, &spectate_mod[1], 1);

		*reinterpret_cast<float*>(0xACE4A8 + 0x10) = *reinterpret_cast<float*>(Unit + obj_Pos_X);
		*reinterpret_cast<float*>(0xACE4A8 + 0x0C) = *reinterpret_cast<float*>(Unit + obj_Pos_Y);
		*reinterpret_cast<float*>(0xACE4A8 + 0x14) = *reinterpret_cast<float*>(Unit + obj_Pos_Z) + 1;
						 
		unsigned long player_guid = *reinterpret_cast<unsigned long*>(Unit + obj_Guid);
		*reinterpret_cast<unsigned long*>(0xACE4A8 + 0x20) = player_guid;
						 
		float cameraSpeed = 100; // Single::TryParse(txtbCameraSpeed->Text, cameraSpeed) ? cameraSpeed : 100;
		*reinterpret_cast<float*>(0xACE4A8 + 0x44) = cameraSpeed;
	}
	else if(stete_Off)
	{
		InternalMemory::WriteProtectedMemory(spectator_base + 0x0A, &spectate_mod[0], 1);
	}

	if(state_Teleport)
	{
		*reinterpret_cast<float*>(Unit + obj_Pos_X) = *reinterpret_cast<float*>(0xACE4A8 + 0x10);
		*reinterpret_cast<float*>(Unit + obj_Pos_Y) = *reinterpret_cast<float*>(0xACE4A8 + 0x0C);
		*reinterpret_cast<float*>(Unit + obj_Pos_Z) = *reinterpret_cast<float*>(0xACE4A8 + 0x14) - 1;

		InternalMemory::WriteProtectedMemory(spectator_base + 0x0A, &spectate_mod[0], 1);
	}

	return TRUE;
}