#pragma once

#include "WoWHack.h"

typedef std::shared_ptr<class MorphHack> MorphHackPtr;

class MorphHack
{
public:
	// Get singleton
	static MorphHackPtr Get()
	{
		static MorphHackPtr pMorphHack;
		if (pMorphHack == 0)
			pMorphHack.reset(new MorphHack());

		return pMorphHack;
	}

	void MorphUnit(DWORD Unit, unsigned int MorphID)
	{
		if(!MorphID)
			MorphID = GetOriginalDisplayID(Unit);

		*reinterpret_cast<unsigned int*>(*reinterpret_cast<unsigned int*>(Unit + Descriptors) + DisplayID) = MorphID;
		unit = Unit;
		requiresMorph = true;
	}

	void MorphMount(DWORD Unit, unsigned int MorphID)
	{
		mountMorphID = MorphID ? MorphID : GetMountOriginalDisplayID(Unit);
		unit = Unit;
		requiresMorphMount = true;
	}

	// Call this from main thread to update MorphID
	void MorphFromMainThread()
	{
		if(requiresMorph)
		{   
			reinterpret_cast<void (__thiscall*)(unsigned int, BOOL)>(CGUnit_C__UpdateDisplayInfo)(unit, TRUE);
			requiresMorph = false;
		}

		if(requiresMorphMount)
		{
			reinterpret_cast<void (__thiscall*)(unsigned int, unsigned int)>(CGUnit_C__OnMountDisplayChanged)(unit, mountMorphID);
			requiresMorphMount = false;
		}
	}

	unsigned int GetOriginalDisplayID(DWORD Unit)
	{
	    return *reinterpret_cast<unsigned int*>(*reinterpret_cast<unsigned int*>(Unit + Descriptors) + OriginalDisplayID);
	}

	unsigned int GetMountOriginalDisplayID(DWORD Unit)
	{
		return *reinterpret_cast<unsigned int*>(*reinterpret_cast<unsigned int*>(Unit + Descriptors) + MountDisplayID);
	}

protected:
	// Constructor (protected to enforce singleton)
	MorphHack() 
		:
		requiresMorph(false),
		requiresMorphMount(false)
		// Initialize globals/function pointers
	{
		//requiresMorph = false;
	}

	// Disable copying and assignment
	MorphHack(MorphHack const&);
	MorphHack& operator= (MorphHack const&);

private:
	
	bool requiresMorph, requiresMorphMount;
	unsigned int unit, mountMorphID;
};