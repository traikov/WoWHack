#pragma once

#include "..\WoWHack.h"

namespace InternalMemory
{
	void WriteProtectedMemory(unsigned int Address, const void* Bytes, unsigned int Size);
}