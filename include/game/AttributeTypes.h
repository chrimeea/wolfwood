#ifndef ATTRIBUTESTYPES_H
#define ATTRIBUTESTYPES_H

struct Attribute
{
	unsigned int nameKey;
};

struct Feature: Attribute
{
	unsigned int scriptId;
	unsigned int levelRequired;
};

struct AttributeValue
{
	unsigned int attributeId;
	int value;
};

#endif