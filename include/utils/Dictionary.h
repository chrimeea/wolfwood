#ifndef DICTIONARY_H
#define DICTIONARY_H

#include "utils\config.h"

class Dictionary
{
private:
	static std::vector<std::string> *dict;
public:
	static void Init();
	static void Close();
	static const char *GetText(unsigned int);
};

#endif