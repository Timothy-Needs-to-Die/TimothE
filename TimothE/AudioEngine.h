#include <fmod.hpp>
#include "fmod.h"

#include <string>
#include <map>
#include <iostream>
#include <math.h>

class AudioEngine
{
public:
	AudioEngine();
	~AudioEngine();

	

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
	
	FMOD::Sound* CreateAudioStream(const char* filePath);
	void LoadSFX(const char* filePath);
	void LoadSoundtrack(const char* filePath);

	void PlaySFX(FMOD::Sound* song);
	void PlaySFX(const char* path, float minVolume, float maxVolume, float minPitch, float maxPitch);
	void PlaySong(FMOD::Sound* song);

	void TogglePaused(FMOD::Channel* channel);
	void SetVolume(FMOD::Channel* channel, float value);

	//Audio Modification
	float ChangeOctave(float frequency, float ammount);
	float ChangeSemitone(float frequency, float ammount);
	void SetPanning(FMOD::Channel* channel, float ammount);
private:
	//Current storage for sounds in a map 
	typedef std::map <const char*, FMOD::Sound*> SoundMap;

	enum AudioType { Type_SFX, Type_Song, Type_Count };

	void Load(AudioType type, const char* filePath);

	FMOD::Channel* currentSong;

	SoundMap _sounds[Type_Count];


	FMOD::System* _fmodSystem;
	FMOD::ChannelGroup* _master;
	FMOD::ChannelGroup* _groups[Type_Count];
	//Modes holds the settings each catagory type to be used while loading the audio data
	FMOD_MODE modes[Type_Count];

	void Initialize();

};

