#ifndef AUDIOENGINE
#define AUDIOENGINE

#pragma warning(disable: 4786)

#include "audio\al\al.h"
#include "audio\al\alc.h"
#include "audio\al\alut.h"
#include <string.h>
#include "utils\config.h"

class AudioEngine
{
private:
   AudioEngine();
   ~AudioEngine();
   static AudioEngine *engine;
   unsigned int EAXlevel;
   std::vector<std::string> *mappings;
public:
	void SetListenerPosition(float*, float*);
	static AudioEngine *GetInstance();
	void Close();
	void SetMasterGain(float);
	std::string GetFile(int id) { return (*mappings)[id]; }
};

#endif
