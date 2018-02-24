#pragma once
#ifndef LOCATOR_H
#define LOCATOR_H

#include "IGameTime.h"
#include "IConfigHandler.h"
#include "IEventHandler.h"
#include "MemoryManager.h"
#include "ID3D.h"

enum class MEMORYTYPE { PERM, STATE, FRAME };

/* Service Locator pattern */

class Locator
{
private:
	static IGameTime* sGT;
	static IConfigHandler* sCH;
	static IEventHandler* sEH;
	static MemoryManager* sPermMem;
	static MemoryManager* sStateMem;
	static MemoryManager* sFrameMem;
	static ID3D* sD3D;

public:
	/*- - - - - - - -<INFORMATION>- - - - - - - -
	1. Provides the address of 'gameTime'(obj) to the 'sGT'(ptr) Locator object.
	2. Passes the pointer to 'gameTime'(obj) as a parameter.
	*/
	static void provide(IGameTime* gameTime);
	static void provide(IConfigHandler* configHandler);
	static void provide(IEventHandler* eventHandler);
	static void provide(MemoryManager* mm, MEMORYTYPE type);
	static void provide(ID3D* d3d);
	
	/*- - - - - - - -<INFORMATION>- - - - - - - -
	1. Returns the 'sGT'(ptr).
	2. 'sGT'(ptr) points to the address of 'gameTime'(obj), thereby returning that address.
	*/
	static IGameTime* getGameTime();
	static IConfigHandler* getConfigHandler();
	static IEventHandler* getEventHandler();
	static MemoryManager* getMemoryManager(MEMORYTYPE type);
	static ID3D* getD3D();
};

#endif
