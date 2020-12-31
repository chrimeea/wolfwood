#ifndef SCENE_H
#define SCENE_H

#include "utils\LinkedList.h"
#include "game\Entity.h"

class Scene
{
private:
	typedef LinkedList<Entity> EntityList;
	EntityList *eList;
	static Scene *instance;
	unsigned int nextId;
	Scene();
	~Scene();
public:
	static Scene *GetInstance();
	unsigned AddEntity(Entity *);
	void RemoveEntity(unsigned);
	void NextFrame(float);
	void RenderAll();
	void Close();
	Entity *GetEntity(unsigned);
};

#endif