#pragma once


//#include "EndSceneHook.h"
#include "..\WoWHack.h"

unsigned int PlayerAddress = 0;
unsigned int TargetAddress = 0;

DirectX9Detour::EndScene_t o_pEndScene;

HRESULT __stdcall DirectX9Detour::hkEndScene(LPDIRECT3DDEVICE9 pDevice)
{
	PlayerAddress = reinterpret_cast<unsigned int (__cdecl*)(const char*)>(0x0060C1F0)("Player");
	TargetAddress = reinterpret_cast<unsigned int (__cdecl*)(const char*)>(0x0060C1F0)("Target");

	// WoWLua::FrameScript_Execute::Get()->ExecuteCommandFromMainThread();
	// Utils::Interact();
	MorphHack::Get()->MorphFromMainThread();

	return o_pEndScene(pDevice);
}

void DirectX9Detour::Initialize()
{   
	unsigned int pDevicePtr_1 = *reinterpret_cast<unsigned int*>(0x00C5DF88);
    unsigned int pDevicePtr_2 = *reinterpret_cast<unsigned int*>(pDevicePtr_1 + 0x397C);
    unsigned int VTable = *reinterpret_cast<unsigned int*>(pDevicePtr_2);
    unsigned int EndSceneAddr = *reinterpret_cast<unsigned int*>(VTable + 0xA8);
	o_pEndScene = reinterpret_cast<EndScene_t>(EndSceneAddr);

	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());
	DetourAttach(&(PVOID&)o_pEndScene, hkEndScene);
	DetourTransactionCommit();
}

unsigned int WoW::GetPlayer()
{
	return PlayerAddress;
}

unsigned int WoW::GetTarget()
{
	return TargetAddress;
}