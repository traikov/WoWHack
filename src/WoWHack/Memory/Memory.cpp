#pragma once

//#include "..\WoWHack.h"
#include "Memory.h"

void InternalMemory::WriteProtectedMemory(unsigned int Address, const void* Bytes, unsigned int Size)
{
	unsigned long oldProtection, newProtection;

	VirtualProtect((void*)Address, Size, PAGE_READWRITE, &oldProtection);
	memcpy((void*)Address, Bytes, Size);
	VirtualProtect((void*)Address, Size, oldProtection, &newProtection);

	FlushInstructionCache(GetCurrentProcess(), (void*)Address, Size);
	return;
}