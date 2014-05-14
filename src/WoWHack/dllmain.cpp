// dllmain.cpp : Defines the entry point for the DLL application.
#include "WoWHack.h"

//#include <process.h>

void WINAPI FixInvalidPtrCheck()
{
    *((int*)0x00D415B8) = 0x00000001;
    *((int*)0x00D415BC) = 0x7FFFFFFF;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		//_beginthread(DirectX9Detour::Initialize);
		//CreateThread(nullptr, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(Misc::LoopKillswitch), nullptr, 0, nullptr);
		CreateThread(nullptr, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(DirectX9Detour::Initialize), nullptr, 0, nullptr);
		CreateThread(nullptr, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(FixInvalidPtrCheck), nullptr, 0, nullptr);
		CreateThread(nullptr, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(ConsoleCommands::Install), nullptr, 0, nullptr);
		break;
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}

