#include <string.h>
#include "utils\Dictionary.h"
#include "utils\Config.h"

std::vector<std::string> *Dictionary::dict = NULL;

void Dictionary::Init()
{
	char *df = Config::GetValue("config/dictionary/dictfile");
	dict = new std::vector<std::string>();
	Config::ReadMappingsV(df, dict);
}

void Dictionary::Close()
{
	free(dict);
}

const char *Dictionary::GetText(unsigned int id)
{
	return (*dict)[id].c_str();
}