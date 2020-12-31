#ifndef AUDIOSOURCE
#define AUDIOSOURCE

#include "audio\al\al.h"
#include "audio\al\alc.h"
#include "audio\al\alut.h"
#include <stdio.h>
#include "audio\ogg\codec.h"
#include "audio\ogg\vorbisfile.h"

class AudioSource
{
private:
	bool Stream(ALuint buffer);
	void Empty();
	FILE *oggFile;
	OggVorbis_File oggStream;
	ALuint buffers[2];
	ALuint source;
	ALenum format;
	vorbis_info* vorbisInfo;
	bool looping;
public:
	AudioSource();
	~AudioSource();
	void SetSourcePosition(float *);
	bool Play();
	void Stop();
	void SetGain(float);
	void OpenAudioFile(unsigned int);
	void SetLooping(bool);
	bool IsPlaying();
	bool Update();
};

#endif
