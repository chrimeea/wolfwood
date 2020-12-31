#include "game\scripting\Console.h"
#include "game\events\EventsManager.h"
#include "game\events\KeyPressedEvent.h"
#include "game\events\Source.h"
#include "rendering\CRenderer.h"
#include "utils\Config.h"
#include "game\scripting\ScriptManager.h"

Console::Console() {
	text = new std::string();
	isActive = false;
	commIndex = 0;
	commSize = 0;
	cx = atoi(Config::GetValue("config/console/startx"));
	cy = atoi(Config::GetValue("config/console/starty"));
	cw = atoi(Config::GetValue("config/console/width"));
	ch = atoi(Config::GetValue("config/console/height"));
	cmax = atoi(Config::GetValue("config/console/history"));
}

void Console::EventOccured(Event *e) {
	unsigned short c = ((KeyPressedEvent *) e)->GetKeyPressed();
	if (isalnum(c)) {
		if (text->size() > cmax) {
			text->erase(text->begin());
		}
		*text += c;
	} else if (c == 8 && text->size() > 0) {
		text->erase(text->end()-1);
		while ((*text)[text->size()-1] == 13) {
			text->erase(text->end()-1);
		}
	} else if (c == 13) {
		commSize = text->size() - commIndex;
		*text += c;
		ScriptManager::GetInstance()->RunCommand((text->substr(commIndex, commSize)).c_str());
	}
	
}

void Console::Activate() {
	if (!isActive) {
		EventsManager::GetInstance()->RegisterObserver(this, EVENT_TYPE_KEYPRESS, SOURCE_TYPE_KEYBOARD);
		isActive = true;
	}
}

void Console::Deactivate() {
	if (isActive) {
		EventsManager::GetInstance()->UnregisterObserver(this, EVENT_TYPE_KEYPRESS, SOURCE_TYPE_KEYBOARD);
		isActive = false;
	}
}

void Console::Render() {
	if (isActive) {
		const char *r = text->c_str();
		char *l = new char[cw];
		char *sl = l;
		int s = text->size();
		int dim = cw * ch;
		if (s > dim) {
			r += s - dim;
		}
		unsigned i = 0;
		unsigned ln = 0;
		CRenderer *cr = CRenderer::GetInstance();
		while (*r) {
			*l = *r;
			i++;
			if (i == cw || *r == 13) {
				*l = 0;
				cr->DrawText(cx, cy - ln * LET_HEIGHT, 255, 255, 255, sl);
				l = sl;
				ln++;
				i = 0;
			} else {
				l++;
			}
			r++;
		}
		if (l != sl) {
			*l = 0;
			cr->DrawText(cx, cy - ln * LET_HEIGHT, 255, 255, 255, sl);
		}
		delete[] sl;
	}
}	