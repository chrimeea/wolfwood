#ifndef KEYPRESSEDEVENT_H
#define KEYPRESSEDEVENT_H

#include "game\events\Event.h"

class KeyPressedEvent: public Event
{
private:
	unsigned short key;
public:
	KeyPressedEvent(Source *s, unsigned short k) : Event(EVENT_TYPE_KEYPRESS, s) {
		key = k;
	}
	unsigned short GetKeyPressed() {
		return key;
	}
};

#endif