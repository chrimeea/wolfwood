#include "game\Character.h"

Character::Character(unsigned int id, float px, float py, unsigned dialogId): AnimatedEntity(id, px, py)
{
	baseAttributes = new AttributeValues();
	skills = new AttributeValues();
	features = new AttributeValues();
	dial = NULL;
}

Character::~Character()
{
	delete baseAttributes;
	delete skills;
	delete features;
	if (dial) delete dial;
}

void Character::ReadDialog(unsigned dialogId)
{
}