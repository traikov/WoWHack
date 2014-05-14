// WoWHack
// Copyright (C) 2013 Filip Traikov
// 
// This program is not associated with or endorsed by Blizzard Entertainment in any way. 
// World of Warcraft is copyright of Blizzard Entertainment.
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

#pragma once

#include "..\WoWHack.h"

namespace WoW
{
	unsigned int GetPlayer();
	unsigned int GetTarget();

	DWORD_PTR GetWoWVMTFunctionPointer(DWORD objectBaseAddress, DWORD functionIntex);
	void Interact(DWORD baseAddress);
	char* GetName(DWORD baseAddress);
}