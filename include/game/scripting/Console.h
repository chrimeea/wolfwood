#ifndef CONSOLE_H
#define CONSOLE_H

#pragma warning(disable : 4786)

#include "game\events\Observer.h"

#include <string>

class Console : public Observer {
private:
	std::string *text;
	int commIndex;
	int commSize;
	bool isActive;
	int cx, cy, cw, ch, cmax;
public:
	Console();

	~Console() {
		if (isActive) {
			Deactivate();
		}
		delete text;
	}

	const char *GetText() {
		return text->c_str();
	}

	void EventOccured(Event *);
	void Deactivate();
	void Activate();
	void Render();

	bool IsActive() {
		return isActive;
	}
};

#endif

