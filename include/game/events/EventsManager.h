#ifndef EVENTSMANAGER_H
#define EVENTSMANAGER_H

#include "game\events\Event.h"
#include "game\events\Observer.h"
#include "utils\LinkedList.h"

struct ObserverInfo
{
	Observer *observer;
	unsigned short eventType;
	unsigned short sourceType;
};

class EventsManager
{
private:
	typedef LinkedList<ObserverInfo> ObserverList;
	ObserverList *observerList;
	static EventsManager *instance;
	EventsManager();
	~EventsManager();
public:
	static EventsManager *GetInstance();
	void Free();
	void TriggerEvent(Event *);
	void RegisterObserver(Observer *, unsigned short, unsigned short);
	void UnregisterObserver(Observer *, unsigned short, unsigned short);
};

#endif