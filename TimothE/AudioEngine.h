#include <fmod.hpp>
#include <string>
#include <map>
#include <iostream>
#include <math.h>



class AudioEngine
{
public:
	AudioEngine();
	~AudioEngine();

	
	//typeDef std::map<

	// == System Functions == // 
	void AudioUpdate();
	void ShutDownAudio();
	void ReleaseSound(FMOD::Sound* sound);
	void CheckForErrors(FMOD_RESULT result);

	// == Grouping and Group Controls == //
	FMOD::ChannelGroup* CreateChanellGroup(const char* name);
	void SetChannelGroup(FMOD::Channel* channelToSet, FMOD::ChannelGroup* groupToSet);
	void AddChildGroup(FMOD::ChannelGroup* parentGroup, FMOD::ChannelGroup* childGroup);
	FMOD::ChannelGroup* GetMasterGroup(FMOD::ChannelGroup* masterGroupObject);

	void StopGroup(FMOD::ChannelGroup* group);

	void ToggleGroupMute(FMOD::ChannelGroup* group);

	void ToggleGroupPause(FMOD::ChannelGroup* group);

	void SetGroupVolume(FMOD::ChannelGroup* group, float value);

	void SetGroupPitch(FMOD::ChannelGroup* group, float value);
	
	// == Core Functionality == // 
	FMOD::Sound* LoadAudio(const char* filePath);
	FMOD::Sound* CreateAudioStream(const char* filePath);

	void PlayOneShot(FMOD::Sound*);
	void TogglePaused(FMOD::Channel* channel);
	void SetVolume(FMOD::Channel* channel, float value);

	//Audio Modification
	float ChangeOctave(float frequency, float ammount);
	float ChangeSemitone(float frequency, float ammount);
	void SetPanning(FMOD::Channel* channel, float ammount);
private:

	FMOD::System* _fmodSystem;
	void Initialize();

};

