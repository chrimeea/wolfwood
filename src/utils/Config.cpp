#pragma warning(disable : 4786)

#include <ctype.h>
#include <string.h>
#include <fstream>
#include "utils\Config.h"

FILE *Config::xml = NULL;
XMLTree *Config::doc = NULL;

void Config::Init()
{
	doc = new XMLTree();
	xml = fopen(CONFIG_FILE, "rt");
	ParseXMLFile();
	fclose(xml);
}

void Config::Close()
{
	delete doc;
}

char *Config::GetValue(char *path)
{
	char *p = path;
	int k = 0;
	XMLTree *cTree = doc;
	char acum[CONFIG_MAX_NAME];
	if (*p == '/') {
		p++;
	}
	while (*p) {
		if (*p == '/') {
			if (!(cTree = FindSon(cTree, acum))) {
				return NULL;
			}
			k = 0;
		} else {
			acum[k++] = *p;
			acum[k] = 0;
		}
		p++;
	}
	if (!k) {
		return cTree->GetData()->tagValue;
	} else {
		if (cTree = FindSon(cTree, acum)) {
			return cTree->GetData()->tagValue;
		}
	}
	return NULL;
}

XMLTree *Config::FindSon(XMLTree *t, const char *name)
{
	XMLTree *xmlT = t->GetFirstSon();
	while (xmlT != NULL)
	{
		if (!strcmp(xmlT->GetData()->tagName, name)) {
			return xmlT;
		}
		xmlT = xmlT->GetSibling();
	}
	return NULL;
}

void Config::ParseXMLFile()
{
	char acum[CONFIG_MAX_NAME];
	int stare = 1, k = 0;
	char c;
	XMLTree *cTree = doc;
	char buf[1024];
	int total = fread(buf, 1, 1024, xml);
	char *cbuf = buf;
	while (stare)
	{
		c = *cbuf;
		if (isspace(c)) {
			if (stare == 2 || stare == 3 || stare == 4 ||
				stare == 5 || stare == 6 || stare == 7 ||
				stare == 8 || stare == 10 || stare == 11) {
				stare = 0;
			}
			k = 0;
		} else if (c == '<') {
			switch (stare) {
				case 1: //inceput de tag <
						if (k > 0) {
							SetTagValue(cTree, acum, k);
						}
						stare = 2;
						break;
				case 9: //comentariu
					    break;
				default: stare = 0;
			}
			k = 0;
		} else if (c == '/') {
			switch (stare) {
				case 1: //valoare
						break;
				case 2: //este un tag care se inchide </
						stare = 3;
						break;
				case 4: //este un tag fara valoare <.../
						stare = 5;
						break;
				case 9: //comentariu
						break;
				default: stare = 0;
			}
			k = 0;
		} else if (c == '>') {
			switch (stare) {
				case 4: //am intrat in interiorul unui tag cu valoare <...>
						cTree = cTree->CreateSon();
						SetTagName(cTree, acum, k);
						stare = 1; //coboram un nivel
						break;
				case 5: //s-a inchis un tag fara valoare <.../>
						cTree = cTree->CreateSon();
						SetTagName(cTree, acum, k);
						cTree = cTree->GetFather();
						stare = 1; //urcam un nivel
						break;
				case 6: //s-a inchis un tag cu valoare </...>
						stare = 1; //urcam un nivel
						if (!CheckTagName(cTree, acum)) {
							stare = 0;
						}
						cTree = cTree->GetFather();
						break;
				case 9: //comentariu
						break;
				case 11: //s-a inchis un comentariu <!--...-->
						stare = 1;
						break;
				default: stare = 0;
			}
			k = 0;
		} else if (c == '!') {
			switch (stare) {
				case 2: //inceput comentariu <!
						stare = 7;
						break;
				default: stare = 0;
			}
			k = 0;
		} else if (c == '-') {
			switch (stare) {
				case 7: //comentariu <!-
						stare = 8;
						break;
				case 8: //comentariu <!--
						stare = 9;
						break;
				case 9:	//comentariu se inchide <!--...-
						stare = 10;
						break;
				case 10: //comentariu se inchide <!--...--
						stare = 11;
						break;
				default: stare = 0;
			}
			k = 0;
		} else {
			acum[k++] = c;
			acum[k] = 0;
			switch(stare) {
				case 1: //valoare
						break;
				case 2: //este un tag care se deschide <...
						stare = 4;
						break;
				case 3: //este un tag care se inchide </...
						stare = 6;
						break;
				case 4: //citim numele tagului <...
						break;
				case 6: //citim numele tagului </...
						break;
				case 9: //comentariu
						break;
				default: stare = 0;
			}
		}
		cbuf++;
		total--;
		if (!total) {
			if (feof(xml)) {
				break;
			}
			total = fread(buf, 1, 1024, xml);
			cbuf = buf;
		}
	}
}

int Config::CheckTagName(XMLTree *t, const char *name)
{
	XMLData *xd = t->GetData();
	if (xd) {
		return !strcmp(xd->tagName, name);
	}
	return 0;
}

void Config::SetTagValue(XMLTree *t, const char *value, int size)
{
	if (!t->GetData()) {
		XMLData *xd = new XMLData();
		xd->tagValue = NULL;
		xd->tagName = NULL;
		t->SetData(xd);
	}
	size += 2;
	char *xmlValue = t->GetData()->tagValue;
	if (!xmlValue) {
		xmlValue = (char *) malloc(size * sizeof(char));
		strcpy(xmlValue, value);
	} else {
		int l = strlen(xmlValue);
		xmlValue = (char *) realloc(xmlValue, (l + size) * sizeof(char));
		strcat(xmlValue, value);
	}
	t->GetData()->tagValue = xmlValue;
}

void Config::SetTagName(XMLTree *t, const char *name, int size)
{
	if (!t->GetData()) {
		XMLData *xd = new XMLData();
		xd->tagName = NULL;
		xd->tagValue = NULL;
		t->SetData(xd);
	}
	size += 2;
	char *xmlName = t->GetData()->tagName;
	if (xmlName) {
		free(xmlName);
	}
	xmlName = (char *) malloc(size * sizeof(char));
	strcpy(xmlName, name);
	t->GetData()->tagName = xmlName;
}

void Config::ReadMappings(const char *f, FileIdMap *m)
{
	std::string strname;
	unsigned int id;
	std::ifstream ifs(f);
	while(!ifs.eof())
	{
		if (ifs.peek() != ';') {
			ifs >> id >> strname;
			m->insert(FileIdMap::value_type(id, strname));
		} else {
			ifs >> strname;
		}
	}
}

void Config::ReadMappingsV(const char *f, std::vector<std::string> *m)
{
	std::string strname;
	unsigned int id;
	std::ifstream ifs(f);
	while(!ifs.eof())
	{
		if (ifs.peek() != ';') {
			ifs >> id >> strname;
			m->push_back(strname);
		} else {
			ifs >> strname;
		}
	}
}

std::string Config::FindMappingById(FileIdMap *m, unsigned id)
{
	FileIdMapIter iter;
	if((iter = m->find(id)) != m->end()) return (*iter).second;
	return NULL;
}
