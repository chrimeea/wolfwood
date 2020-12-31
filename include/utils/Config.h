#ifndef CONFIG
#define CONFIG

#pragma warning(disable : 4786)

#include <stdio.h>
#include <map>
#include <string>
#include <vector>
#include "utils\Tree.h"

#define CONFIG_FILE "wolfwood.xml"
#define CONFIG_MAX_NAME 50

struct XMLData {
	char *tagName;
	char *tagValue;
};

typedef Tree<struct XMLData> XMLTree;
typedef std::map<unsigned int, std::string> FileIdMap;
typedef FileIdMap::iterator FileIdMapIter;

class Config
{
private:
	static FILE *xml;
	static XMLTree *doc;
	static void ParseXMLFile();
	static void SetTagName(XMLTree *, const char *, int);
	static void SetTagValue(XMLTree *, const char *, int);
	static int Config::CheckTagName(XMLTree *t, const char *name);
	static XMLTree *FindSon(XMLTree *t, const char *name);
	Config() {}
	~Config() {}
public:
	static char *GetValue(char *);
	static void Init();
	static void Close();
	static void ReadMappings(const char *, FileIdMap *);
	static void ReadMappingsV(const char *, std::vector<std::string> *);
	static std::string FindMappingById(FileIdMap *, unsigned);
};

#endif
