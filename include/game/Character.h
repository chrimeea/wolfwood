#ifndef CHARACTER_H
#define CHARACTER_H

#include "game\AttributeTypes.h"
#include "game\AnimatedEntity.h"
#include "utils\LinkedList.h"
#include "utils\Tree.h"

struct Dialog
{
	unsigned id;
	unsigned option;
	unsigned answer;
	unsigned intelligence;
	unsigned charisma;
	bool lock;
	unsigned script_o;
	unsigned script_a;
	unsigned script_n;
};

class Character: AnimatedEntity
{
protected:
	typedef LinkedList<AttributeValue> AttributeValues;
	typedef Tree<Dialog> DialogTree;
	AttributeValues *baseAttributes;
	AttributeValues *skills;
	AttributeValues *features;
	unsigned level;
	DialogTree *dial;
	void ReadDialog(unsigned);
public:
	Character(unsigned, float, float, unsigned);
	virtual ~Character();
};

#endif
