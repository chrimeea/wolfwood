#ifndef OBSERVER_H
#define OBSERVER_H

#include "game\events\Event.h"

class Observer
{
public:
	virtual void EventOccured(Event *) = 0;
};

#endif