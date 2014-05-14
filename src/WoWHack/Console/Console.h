#pragma once

// C++ Standard Library
#include <set>
#include <string>
#include <memory>

// WoWConsole pointer type
typedef std::tr1::shared_ptr<class WoWConsole> WoWConsolePtr;

// Wrapper class for WoW's console
class WoWConsole
{
public:
  // Get singleton
  static WoWConsolePtr Get()
  {
    static WoWConsolePtr pConsole;
    if (pConsole == 0)
      pConsole.reset(new WoWConsole());
    return pConsole;
  }

  // WoW engine console command groups
  enum ConsoleCmdGroup
  {
    Debug,
    Graphics,
    Console,
    Combat,
    Game,
    Default,
    Net,
    Sound,
    Gm
  };

  // WoW engine console callback function type
  typedef int (__cdecl* tCallback)(char const* cmd, char const* args);

  // Register a console command
  // Note: Neither 'Name' nor 'Help' are copied internally and hence the 
  // pointers must remain valid for the lifetime of the command.
  // Note: 'Help' is optional (null pointer is valid)
  long CommandRegister(char const* Name, tCallback Callback, 
    ConsoleCmdGroup Group, char const* Help)
  {
    //m_CmdNames.insert(Name);
    return m_pCmdRegister(Name, Callback, Group, Help);
  }

  // Unregister a console command
  long CommandUnregister(std::string const& Name)
  {
    std::set<std::string>::iterator i = m_CmdNames.find(Name);
    if (i != m_CmdNames.end())
      m_CmdNames.erase(i);
    m_pCmdUnregister(Name.c_str());
  }

  // Destructor
  ~WoWConsole()
  {
    // Unregister all registered commands
   /* for (std::set<std::string>::const_iterator i = m_CmdNames.begin(); 
      i != m_CmdNames.end(); ++i)
    {
      m_pCmdUnregister(i->c_str());
    }*/
  }

protected:
  // Constructor (protected to enforce singleton)
  WoWConsole() 
    // Initialize engine global/function pointers
    : 
    m_pCmdRegister(reinterpret_cast<tCmdRegister>(0x00769100)), 
    m_pCmdUnregister(reinterpret_cast<tCmdUnregister>(0x007689E0)), 
    m_CmdNames()
  {
  }

  // Disable copying and assignment
  WoWConsole(WoWConsole const&);
  WoWConsole& operator= (WoWConsole const&);

private:
  // WoW engine function to register a console callback
  typedef long (__cdecl* tCmdRegister)(char const* Name, tCallback Callback, 
    ConsoleCmdGroup Group, char const* Help);
  tCmdRegister m_pCmdRegister;

  // WoW engine function to unregister a console callback
  typedef long (__cdecl* tCmdUnregister)(char const* CmdName);
  tCmdUnregister m_pCmdUnregister;

  // List of callbacks registered (needed so they can be unregistered 
  // in the destructor)
  std::set<std::string> m_CmdNames;
};