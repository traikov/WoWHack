#pragma once

#include "..\WoWHack.h"

namespace WoWLua
{
	typedef std::shared_ptr<class FrameScript_Execute> FrameScript_ExecutePtr;

	class FrameScript_Execute
	{
	public:
		// Get singleton
		static FrameScript_ExecutePtr Get()
		{
			static FrameScript_ExecutePtr pConsole;
			if (pConsole == 0)
				pConsole.reset(new FrameScript_Execute());

			return pConsole;
		}

		void ExecuteCommand(std::string command)
		{
			o_pExecuteCommand(command.c_str(), command.c_str(), nullptr);
			//this->command = command;
			//requiresExecuting = true;
		}

		/*void ExecuteCommandFromMainThread()
		{
			if(requiresExecuting)
			{
				o_pExecuteCommand(command.c_str(), command.c_str(), nullptr);
				requiresExecuting = false;
			}
		}*/

	protected:
		// Constructor (protected to enforce singleton)
		FrameScript_Execute() 
			// Initialize globals/function pointers
			: o_pExecuteCommand(reinterpret_cast<tExecuteCommand>(FrameScript_ExecuteAddress)),
			command()
		{
		}

		// Disable copying and assignment
		FrameScript_Execute(FrameScript_Execute const&);
		FrameScript_Execute& operator= (FrameScript_Execute const&);

	private:
		typedef void (__cdecl* tExecuteCommand)(const char* sCommand1,const char* sCommand2, void* pState /*  = nullptr */);
		tExecuteCommand o_pExecuteCommand; 

		bool requiresExecuting;
		std::string command; // backing field -- we need a copy of the given command
	};
}