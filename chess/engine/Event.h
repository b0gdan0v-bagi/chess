#pragma once

#include <unordered_map>
#include <algorithm>
#include "Singleton.h"


class EventBase
{
	
};

class EventManager
{

};

typedef Singletons<EventManager> EventManagerSingleton;
#define EventManager (EventManagerSingleton::ref())
