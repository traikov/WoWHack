#pragma once

#include "WoWHack.h"

const unsigned ThisVersion = 1;
bool HasChecked = false;

void Misc::LoopKillswitch()
{
	CheckKillswitch();
	HasChecked = true;

	while(true)
	{
		Sleep(60000); // 1 minute
		CheckKillswitch();
	}
}

void Misc::CheckKillswitch ()
{
	try
	{
		char* Path = new char[261];
		ZeroMemory(Path, 261);

		if(URLDownloadToCacheFileA(NULL, "https://dl.dropboxusercontent.com/u/209978287/KillSwitch.txt", Path, 260, 0, NULL) != S_OK && HasChecked == false)
		{
			throw std::exception("Unable to check killswitch: File download failed.");
		}

		std::fstream* KillSwitch = new std::fstream(Path, std::ios::in);
		if(KillSwitch->is_open() == false && HasChecked == false)
		{
			throw std::exception("Unable to check killswitch: Failed to open file.");
		}

		std::string* Contents = new std::string[2];
		std::getline(*KillSwitch, Contents[0]);
		std::getline(*KillSwitch, Contents[1]);
		KillSwitch->close();
		delete KillSwitch;
		DeleteFileA(Path);
		delete[] Path;

		if(Contents->find("Enabled") == Contents->npos)
		{
			// if(HasChecked == false)
			{
				MessageBoxA(nullptr, Contents->c_str(), "Message", MB_ICONINFORMATION);
			}

			exit(0);
		}

		static unsigned int Version = ThisVersion;
		unsigned int NewVersion = atoi(Contents[1].c_str());
		if(NewVersion > Version)
		{ 
			if(MessageBoxA(nullptr, "A new version of WoWHack is available. Open the download page ?" , "New Version", MB_YESNO) == IDYES)
			{
				ShellExecuteA(NULL, "open", "http://wowcheat.hit.bg/WoWHack/WoWHack.zip", NULL, NULL, 0);
			}
			
			Version = NewVersion;
		}

		delete Contents;
	}
	catch(std::exception& e)
	{
		MessageBoxA(nullptr, e.what(), "Exception", MB_ICONWARNING);
		exit(0);
	}
}