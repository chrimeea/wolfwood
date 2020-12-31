#ifndef EVENT_H
#define EVENT_H

#include "game\events\Source.h"

#define EVENT_TYPE_ALL 0
#define EVENT_TYPE_MOVE 1
#define EVENT_TYPE_KEYPRESS 2

class Event
{
private:
	unsigned short type;
	Source *source;
public:
	Event(unsigned short t, Source *s) {
		type = t;
		source = s;
	}
	unsigned short GetType() {
		return type;
	}
	Source *GetSource() {
		return source;
	}
	bool Equals(unsigned short evType, unsigned short srcType) {
		if ((type == evType || type == EVENT_TYPE_ALL) &&
		   (source->GetType() == srcType || source->GetType() == SOURCE_TYPE_ALL)) {
			return true;
		}
		return false;
	}
};

#endif
