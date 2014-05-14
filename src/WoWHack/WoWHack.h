// WoWHack.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windows.h>

// DirectX9
#include <d3d9.h>
#pragma comment(lib, "d3d9.lib")

// MS Detours
#include <detours.h>
#pragma comment(lib, "detours.lib")

// C++ Standard Library
#include <string>
#include <memory>
#include <fstream>

// Windows Specific
#include <Shellapi.h>

#include <Urlmon.h>
#pragma comment (lib, "UrlMon.lib")

// WoWHack
#include "Offsets.h"
#include "Utils\Helper.h"
#include "Memory\Memory.h"
#include "WoWFunctions\WoWFunctions.h"
#include "WoWLua\FrameScript_Execute.h"
#include "WoWLua\GetText.h"
#include "DirectXDetours\EndSceneHook.h"
#include "Console\Console.h"
#include "Console\ConsoleCommands.h"
#include "MorphHack.h"
#include "Misc.h"
