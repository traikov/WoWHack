#pragma once

#include "..\WoWHack.h"

typedef void (__thiscall *tInteract)(DWORD BaseAddress);
tInteract oInteract;

typedef char* (__thiscall *tGetName)(DWORD BaseAddress);
tGetName oGetName;


DWORD_PTR WoW::GetWoWVMTFunctionPointer(DWORD objectBaseAddress, DWORD functionIntex)
{
	return *reinterpret_cast<DWORD_PTR*>(*reinterpret_cast<DWORD_PTR*>(objectBaseAddress) + (functionIntex *4));
}

void WoW::Interact(DWORD baseAddress)
{
	//DWORD_PTR objectInteractVMT = *reinterpret_cast<DWORD_PTR*>(*reinterpret_cast<DWORD_PTR*>(baseAddress) + (44 *4));
	DWORD_PTR objectInteractVMT  = WoW::GetWoWVMTFunctionPointer(baseAddress, 44);
	oInteract = reinterpret_cast<tInteract>(objectInteractVMT);
	oInteract(baseAddress);
}

char* WoW::GetName(DWORD baseAddress)
{
	//DWORD_PTR objectGetName = *reinterpret_cast<DWORD_PTR*>(*reinterpret_cast<DWORD_PTR*>(baseAddress) + (54 *4));
	DWORD_PTR objectGetName = WoW::GetWoWVMTFunctionPointer(baseAddress, 54);
	oGetName = reinterpret_cast<tGetName>(objectGetName);
	return oGetName(baseAddress);
}





//void Interact::WithObject(DWORD baseAddress)
//{
//	DWORD_PTR objectInteractVMT = *reinterpret_cast<DWORD_PTR*>(*reinterpret_cast<DWORD_PTR*>(baseAddress) + (44 *4));
//	tInteract oInteract = reinterpret_cast<tInteract>(objectInteractVMT);
//	oInteract(baseAddress);
//}