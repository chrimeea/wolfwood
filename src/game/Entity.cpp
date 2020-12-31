#include "game\Entity.h"
#include "rendering\CMesh.h"
#include "game\Scene.h"
#include "background\Background.h"
#include "game\events\EventsManager.h"
#include "game\events\MoveEvent.h"

#include "utils\Logger.h"

Entity::Entity() : Source(SOURCE_TYPE_ENTITY)
{
	posX = posY = 0.0;
	destX = destY = 0.0;
	moving = false;
	id = 0;
}

Entity::Entity(float px, float py) : Source(SOURCE_TYPE_ENTITY)
{
	posX = px;
	posY = py;
	destX = posX;
	destY = posY;
	moving = false;
	id = 0;
}

Entity::~Entity() {
	delete mesh;
}

void Entity::Render()
{
	Background *b = Background::GetInstance();
	if (b->IsVisible((unsigned) posX, (unsigned) posY)) {
		CRenderer::GetInstance()->BeginRenderToPos(b->MapXToScreenX(posX),
			b->MapYToScreenZ(posY));
		mesh->Render();
		CRenderer::GetInstance()->EndRenderToPos();
	}
}

void Entity::NextFrame(float frameTime)
{
	if (moving)
	{
		perc += 0.01f;
		posX = perc * intermX + origX;
		posY = perc * intermY + origY;
		if (perc >= 1.0f) ComputeInterm();
	}
}

void Entity::ComputeInterm()
{
	if (pathIndex == plength) {
		EndMove();
		return;
	}
	unsigned tx, ty;
	tx = path[pathIndex++];
	ty = path[pathIndex++];
	origX = posX;
	origY = posY;
	intermX = (float) tx - origX;
	intermY = (float) ty - origY;
	perc = 0.0f;
	EventsManager::GetInstance()->TriggerEvent(
		new MoveEvent(this, Background::GetInstance()->TileNumber(tx, ty)));
}

void Entity::EndMove()
{
	moving = false;
	if (path != NULL) free(path);
}

void Entity::TranslateTo(float px, float py)
{
	destX = px;
	destY = py;
	moving = true;
	path = Background::GetInstance()->FindPath(posX, posY, destX, destY, &plength);
	plength *= 2;
	pathIndex = 0;
	ComputeInterm();
}