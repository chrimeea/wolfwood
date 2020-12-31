#include "game\AttributeManager.h"
#include "utils\Config.h"

AttributeManager *AttributeManager::instance = NULL;

AttributeManager *AttributeManager::GetInstance()
{
	if (instance == NULL)
	{
		instance = new AttributeManager();
	}
	return instance;
}

void AttributeManager::Close()
{
	if (instance != NULL)
	{
		delete instance;
	}
}

AttributeManager::~AttributeManager()
{
	for (unsigned int i = 0; i < total; i++) {
		delete attributes[i];
	}
	free(attributes);
}

AttributeManager::AttributeManager()
{
	unsigned int k = 0;
	total = atoi(Config::GetValue("config/attributes/total"));
    attributes = (Attribute **) malloc(total * sizeof(Attribute *));
	char *fileName = Config::GetValue("config/attributes/basefile");
	if (fileName) {
		k = ReadBaseAttributes(fileName, k);
	}
	fileName = Config::GetValue("config/attributes/skillsfile");
	if (fileName) {
		k = ReadSkills(fileName, k);
	}
	fileName = Config::GetValue("config/attributes/featuresfile");
	if (fileName) {
		k = ReadFeatures(fileName, k);
	}
}

unsigned int AttributeManager::ReadBaseAttributes(char *fileName, unsigned int k)
{
	FILE *f = fopen(fileName, "rt");
	if (!f) {
		return k;
	}
	unsigned int key;
	while (fscanf(f, "%u\n", &key) != EOF)
	{
		Attribute *a = new Attribute();
		a->nameKey = key;
		attributes[k++] = a;
	}
	fclose(f);
	return k;
}

unsigned int AttributeManager::ReadSkills(char *fileName, unsigned int k)
{
	FILE *f = fopen(fileName, "rt");
	if (!f) {
		return k;
	}
	unsigned int key;
	while (fscanf(f, "%u\n", &key) != EOF)
	{
		Attribute *a = new Attribute();
		a->nameKey = key;
		attributes[k++] = a;
	}
	fclose(f);
	return k;
}

unsigned int AttributeManager::ReadFeatures(char *fileName, unsigned int k)
{
	FILE *f = fopen(fileName, "rt");
	if (!f) {
		return k;
	}
	unsigned int key, sId, lReq;
	while (fscanf(f, "%u %u %u", &key, &sId, &lReq) != EOF)
	{
		Feature *a = new Feature();
		a->nameKey = key;
		a->scriptId = sId;
		a->levelRequired = lReq;
		fscanf(f, "\n");
		attributes[k++] = a;
	}
	fclose(f);
	return k;
}

Attribute *AttributeManager::GetAttribute(unsigned int id)
{
	return attributes[id];
}