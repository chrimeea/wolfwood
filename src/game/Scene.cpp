#include "game\Scene.h"
#include "game\Entity.h"

Scene *Scene::instance = NULL;

Scene *Scene::GetInstance()
{
	if (instance == NULL) {
		instance = new Scene();
	}
	return instance;
}

Scene::Scene() {
	eList = new EntityList();
	nextId = 1;
}

Scene::~Scene() {
	delete instance;
	delete eList;
}

unsigned int Scene::AddEntity(Entity *e)
{
	eList->addNode(e);
	e->id = nextId++;
	return e->id;
}

void Scene::RemoveEntity(unsigned int entid)
{
	eList->head();
	while (!eList->isAtEnd())
	{
		if (eList->getData()->id == entid) {
			eList->delCurrentNode();
		}
	}
}

void Scene::NextFrame(float frameTime)
{
	eList->head();
	while (!eList->isAtEnd())
	{
		eList->getData()->NextFrame(frameTime);
		eList->next();
	}
}

void Scene::RenderAll()
{
	eList->head();
	while (!eList->isAtEnd())
	{
		eList->getData()->Render();
		eList->next();
	}
}

void Scene::Close()
{
	if (instance != NULL)
	{
		delete instance;
	}
}

Entity *Scene::GetEntity(unsigned entityId) {
	eList->head();
	while (!eList->isAtEnd())
	{
		Entity *e = eList->getData();
		if (e->id == entityId) {
			return e;
		}
		eList->next();
	}
	return NULL;
}