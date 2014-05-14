#pragma once

#include "..\WoWHack.h"

namespace WoWLua
{
	typedef std::shared_ptr<class GetText> GetTextPtr;

	class GetText
	{
	public:
		// Get singleton
		static GetTextPtr Get()
		{
			static GetTextPtr pConsole;
			if (pConsole == 0)
				pConsole.reset(new GetText());

			return pConsole;
		}

		char* GetLocalizedText(const char* text)
		{
			return o_pGetText(reinterpret_cast<void*>(WoW::GetPlayer()), text, -1);
		}

	protected:
		// Constructor (protected to enforce singleton)
		GetText() 
			// Initialize globals/function pointers
			: o_pGetText(reinterpret_cast<tGetText>(0x00819D40))  // GetText = 0x00819D40 ; GetLocalizedText = 0x007225E0
		{
		}

		// Disable copying and assignment
		GetText(FrameScript_Execute const&);
		GetText& operator= (GetText const&);

	private:
		// GetText
		typedef char* (__thiscall * tGetText)(void* pThis, const char* sText, DWORD_PTR unk1);
		tGetText o_pGetText; 

		bool requiresExecuting;
	};
}