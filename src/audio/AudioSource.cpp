#include "audio\AudioSource.h"
#include "audio\AudioEngine.h"

#define BUFFER_SIZE 4096 * 8

#include "utils\Logger.h"

AudioSource::AudioSource()
{
	looping = false;
	alGetError();
	alGenSources(1, &source);
	alGenBuffers(2, buffers);
	if(alGetError() != AL_NO_ERROR) {
		//eroare
		//crere sursa
	}
	alSource3f(source, AL_POSITION, 0.0, 0.0, 0.0);
	alSource3f(source, AL_VELOCITY, 0.0, 0.0, 0.0);
    alSource3f(source, AL_DIRECTION, 0.0, 0.0, 0.0);
    alSourcef(source, AL_ROLLOFF_FACTOR, 0.0);
    alSourcei(source, AL_SOURCE_RELATIVE, AL_TRUE);
}

AudioSource::~AudioSource()
{
	alSourceStop(source);
	Empty();
	alDeleteSources(1, &source);
    alDeleteBuffers(1, buffers);
    ov_clear(&oggStream);
}

void AudioSource::SetSourcePosition(float *position)
{
	alSourcefv(source, AL_POSITION, position);
}

void AudioSource::Stop()
{
	alSourceStop(source);
}

bool AudioSource::Play()
{
	if(IsPlaying())
	{
		return true;
	}
	if(!Stream(buffers[0]))
	{
		return false;
	}
	if(!Stream(buffers[1]))
	{
		return false;
	}
	alSourceQueueBuffers(source, 2, buffers);
    alSourcePlay(source);
	return true;
}

void AudioSource::OpenAudioFile(unsigned int fileId)
{
	if(!(oggFile = fopen(AudioEngine::GetInstance()->GetFile(fileId).c_str(), "rb")))
	{
		//Could not open Ogg file
		return;
	}
	if(ov_open(oggFile, &oggStream, NULL, 0) < 0)
	{
		fclose(oggFile);
		return;
		//Could not open Ogg stream;
	}
	vorbisInfo = ov_info(&oggStream, -1);
	if(vorbisInfo->channels == 1)
	{
		format = AL_FORMAT_MONO16;
	} else {
		format = AL_FORMAT_STEREO16;
	}
}

void AudioSource::SetLooping(bool loop)
{
	looping = loop;
}

void AudioSource::SetGain(float gain)
{
	alSourcef(source, AL_GAIN, gain);
}

bool AudioSource::IsPlaying()
{
	int state = 0;
	alGetSourcei(source, AL_SOURCE_STATE, &state);
	return (state == AL_PLAYING);
}

bool AudioSource::Update()
{
    int processed;
    bool active = true;
	alGetSourcei(source, AL_BUFFERS_PROCESSED, &processed);
	while(processed--)
    {
		ALuint buffer;
		alSourceUnqueueBuffers(source, 1, &buffer);
		active = Stream(buffer);
		if (!active && looping) {
			ov_raw_seek(&oggStream, 0);
			active = Stream(buffer);
		}
		alSourceQueueBuffers(source, 1, &buffer);
    }
	return active;
}

bool AudioSource::Stream(ALuint buffer)
{
    char data[BUFFER_SIZE];
    int  size = 0;
    int  section;
    int  result;
	while(size < BUFFER_SIZE)
    {
        result = ov_read(&oggStream, data + size, BUFFER_SIZE - size, 0, 2, 1, &section);
		if(result > 0)
		{
            size += result;
		} else if(result < 0)
		{
			//eroare;
			break;
		} else {
			break;
		}
	}
	if(size == 0)
	{
		return false;
	}
	alBufferData(buffer, format, data, size, vorbisInfo->rate);
	return true;
}

void AudioSource::Empty()
{
    int queued;
	alGetSourcei(source, AL_BUFFERS_QUEUED, &queued);
	while(queued--)
    {
        ALuint buffer;
		alSourceUnqueueBuffers(source, 1, &buffer);
    }
}
