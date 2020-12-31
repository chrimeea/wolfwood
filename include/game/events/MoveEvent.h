#ifndef MOVEEVENT_H
#define MOVEEVENT_H

#include "game\events\Event.h"

class MoveEvent : public Event
{
private:
	unsigned int tile;
public:
	MoveEvent(Source *s, unsigned int ti) : Event(EVENT_TYPE_MOVE, s)
	{
		tile = ti;
	}
	unsigned int GetTile() {
		return tile;
	}
};

#endif