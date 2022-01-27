
#include "pch.h"
#include "fmod.h"

enum AudioType { Type_SFX, Type_Song, Type_Count };

struct SoundStruct {

	const char* filePath;
	FMOD::Sound* sound;
	const char* name;
	AudioType type;
	
};

class AudioEngine
{
public:
	AudioEngine();
	~AudioEngine();

	// == System Functions == // 
	void AudioUpdate(float elapsed);
	void ShutDownAudio();
	void ReleaseSound(FMOD::Sound* sound);
	void CheckForErrors(FMOD_RESULT result);
	float RandomBetween(float min, float max);

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
	SoundStruct LoadSound(const char* name, const char* filePath, AudioType type);
	
	//void PlaySFX(FMOD::Sound* song);
	void PlaySFX(SoundStruct sound, float minVolume, float maxVolume, float minPitch, float maxPitch);
	//void PlaySong(const char* filePath);
	void PlaySong(SoundStruct soundTrack);
	void StopSongs();

	void TogglePaused(FMOD::Channel* channel);
	void SetVolume(FMOD::Channel* channel, float value);

	//Audio Modification
	float ChangeOctave(float frequency, float ammount);
	float ChangeSemitone(float frequency, float ammount);
	void SetPanning(FMOD::Channel* channel, float ammount);

	void SetMasterVolume(float volume);
	void SetSFXVolume(float volume);
	void SetMusicVolume(float volume);
private:
	//Test storage
	SoundStruct titleMusic; 

	//Song stuff
	FMOD::Channel* _currentSongChannel;
	const char* _currentSongPath;
	SoundStruct _nextSong;

	enum FadeState{Fade_None, Fade_In, Fade_Out};
	FadeState fade;

	FMOD::System* _fmodSystem;
	FMOD::ChannelGroup* _master;
	FMOD::ChannelGroup* _groups[Type_Count];
	//Modes holds the settings each catagory type to be used while loading the audio data
	FMOD_MODE modes[Type_Count];

	void Initialize();

};

