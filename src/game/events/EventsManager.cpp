#include "game\events\EventsManager.h"

EventsManager *EventsManager::instance = NULL;

EventsManager::EventsManager()
{
	observerList = new ObserverList();
}

EventsManager::~EventsManager()
{
	delete observerList;
}

void EventsManager::Free()
{
	if (instance != NULL) {
		delete instance;
	}
}

EventsManager *EventsManager::GetInstance()
{
	if (instance == NULL) {
		instance = new EventsManager();
	}
	return instance;
}

void EventsManager::TriggerEvent(Event *e)
{
	observerList->head();
	while (!observerList->isAtEnd())
	{
		ObserverInfo *info = observerList->getData();
		if (e->Equals(info->eventType, info->sourceType)) {
			info->observer->EventOccured(e);
		}
		observerList->next();
	}
}

void EventsManager::RegisterObserver(Observer *o, unsigned short evType, unsigned short srcType)
{
	ObserverInfo *info = new ObserverInfo();
	info->eventType = evType;
	info->sourceType = srcType;
	info->observer = o;
	observerList->addNode(info);
}

void EventsManager::UnregisterObserver(Observer *o, unsigned short evType, unsigned short srcType)
{
	observerList->head();
	while (!observerList->isAtEnd())
	{
		ObserverInfo *info = observerList->getData();
		if (evType == info->eventType && srcType == info->sourceType && info->observer == o) {
			observerList->delCurrentNode();
			break;
		}
	}
}