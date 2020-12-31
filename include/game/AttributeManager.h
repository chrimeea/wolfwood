#ifndef ATTRIBUTEMANAGER_H
#define ATTRIBUTEMANAGER_H

#include "game\AttributeTypes.h"

class AttributeManager
{
private:
	Attribute **attributes;
	unsigned int total;
	static AttributeManager *instance;
	AttributeManager();
	~AttributeManager();
	unsigned int ReadBaseAttributes(char *, unsigned int);
	unsigned int ReadSkills(char *, unsigned int);
	unsigned int ReadFeatures(char *, unsigned int);
public:
	static AttributeManager *GetInstance();
	static void Close();
	Attribute *GetAttribute(unsigned int);
};

#endif