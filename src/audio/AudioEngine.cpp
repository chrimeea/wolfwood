#include "audio\AudioEngine.h"
#include <stdio.h>
#include <string.h>

#define USE_EAX
#ifdef USE_EAX
#define OPENAL
#include <objbase.h>
#include <initguid.h>
#include "audio\al\eax.h"
#endif

AudioEngine *AudioEngine::engine = NULL;

AudioEngine::AudioEngine()
{
	char *mf = Config::GetValue("config/audio/file");
	mappings = new std::vector<std::string>();
	if (mf) {
		Config::ReadMappingsV(mf, mappings);
	}
	EAXlevel = 0;
	alutInit (NULL, 0); // init OpenAL

	// global settings
	alListenerf(AL_GAIN, 1.0);
	alDopplerFactor(1.0); // don't exaggerate doppler shift
	alDopplerVelocity(343); // using meters/second
	alDistanceModel(AL_INVERSE_DISTANCE);

	#ifdef USE_EAX
	// determine EAX support level
	if (alIsExtensionPresent((ALubyte *)"EAX2.0") == AL_TRUE)
	{
		EAXlevel = 2;
	} else
	{
		if (alIsExtensionPresent((ALubyte *)"EAX") == AL_TRUE)
		{
			EAXlevel = 1;
		}
	}

	// set EAX environment if EAX is available
	EAXSet pfPropSet;
	//EAXGet pfPropGet;
	unsigned long ulEAXVal;
	long lGlobalReverb;
	if (EAXlevel)
	{
		pfPropSet = (EAXSet) alGetProcAddress((ALubyte *)"EAXSet");
		if (pfPropSet)
		{
		    lGlobalReverb = -10000;
			pfPropSet(&DSPROPSETID_EAX_ListenerProperties, DSPROPERTY_EAXLISTENER_ROOM, 0, &lGlobalReverb, sizeof(unsigned long));
			ulEAXVal = EAX_ENVIRONMENT_GENERIC;
			pfPropSet(&DSPROPSETID_EAX_ListenerProperties, DSPROPERTY_EAXLISTENER_ENVIRONMENT, 0, &ulEAXVal, sizeof(unsigned long));
		}
	}
	#endif
}

AudioEngine::~AudioEngine()
{
	if(mappings != NULL) delete mappings;
	alutExit();
}

void AudioEngine::SetListenerPosition(ALfloat* position, ALfloat* angle)
{
	alListenerfv(AL_POSITION, position);
	alListenerfv(AL_ORIENTATION, angle);
}

void AudioEngine::Close()
{
	if (engine != NULL)
	{
		delete engine;
	}
}

AudioEngine *AudioEngine::GetInstance()
{
	if (engine == NULL)
	{
		engine = new AudioEngine();
	}
	return engine;
}

void AudioEngine::SetMasterGain(ALfloat gain)
{
	alListenerf(AL_GAIN, gain);
}
