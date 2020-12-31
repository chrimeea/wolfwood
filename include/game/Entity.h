#ifndef ENTITY_H
#define ENTITY_H

#include "rendering\CMesh.h"
#include "game\events\Source.h"

class Entity : Source
{
protected:
	CMesh *mesh;
	float posX, posY, destX, destY, perc, origX, origY, intermX, intermY;
	bool moving;
	unsigned int *path;
	Entity();
	Entity(float, float);
	unsigned int pathIndex, plength;
	virtual void EndMove();
	void ComputeInterm();
public:
	unsigned int id;
	virtual ~Entity();
	virtual void NextFrame(float);
	void Render();
	void TranslateTo(float, float);
};

#endif