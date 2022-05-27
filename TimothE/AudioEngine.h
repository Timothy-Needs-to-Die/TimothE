#pragma once
#include "pch.h"
#include "fmod.h"
#include <map>
#include "Component.h"


enum AudioType { Type_SFX, Type_Song, Type_Count };

struct SoundStruct {
	const char* filePath;
	FMOD::Sound* sound;
	const char* name;
	AudioType type;
};

static class AudioEngine
{
public:
	AudioEngine();
	~AudioEngine();

	// == System Functions == // 
	static void AudioUpdate(float elapsed);
	static void ShutDownAudio();
	static void ReleaseSound(FMOD::Sound* sound);
	static bool CheckForErrors(FMOD_RESULT result);
	static float RandomBetween(float min, float max);

	//This should be set to whatever position the listener is, either the camera or the player itself
	static void Set3DListenerAttributes(FMOD_VECTOR position, FMOD_VECTOR vel, FMOD_VECTOR forward, FMOD_VECTOR up);

	// == Grouping and Group Controls == //
	static FMOD::ChannelGroup* CreateChanellGroup(const char* name);
	static void SetChannelGroup(FMOD::Channel* channelToSet, FMOD::ChannelGroup* groupToSet);
	static void AddChildGroup(FMOD::ChannelGroup* parentGroup, FMOD::ChannelGroup* childGroup);
	static FMOD::ChannelGroup* GetMasterGroup(FMOD::ChannelGroup* masterGroupObject);
	static void StopGroup(FMOD::ChannelGroup* group);
	static void ToggleGroupMute(FMOD::ChannelGroup* group);
	static void ToggleGroupPause(FMOD::ChannelGroup* group);
	static void SetGroupVolume(FMOD::ChannelGroup* group, float value);
	static void SetGroupPitch(FMOD::ChannelGroup* group, float value);

	// == Core Functionality == // 

	static FMOD::Sound* CreateAudioStream(const char* filePath);
	static void LoadSound(const char* name, const char* filePath, AudioType type);
	static FMOD::Channel* PlaySound(std::string soundName, float minVolume, float maxVolume, float minPitch, float maxPitch);
	static void StopSongs();
	static void TogglePaused(FMOD::Channel* channel);
	static void SetVolume(FMOD::Channel* channel, float value);

	//Audio Modification
	float ChangeOctave(float frequency, float amount);
	static float ChangeSemitone(float frequency, float amount);
	static void SetPanning(FMOD::Channel* channel, float amount);
	static void SetMasterVolume(float volume);
	static void SetSFXVolume(float volume);
	static void SetMusicVolume(float volume);
	static enum FadeState { Fade_None, Fade_In, Fade_Out };

private:
	//Test storage
	SoundStruct titleMusic;

	//Song stuff
	static FMOD::Channel* _currentSongChannel;
	static const char* _currentSongPath;
	static SoundStruct _nextSong;


	static FadeState fade;

	static FMOD::System* _fmodSystem;
	static FMOD::ChannelGroup* _master;
	static FMOD::ChannelGroup* _groups[Type_Count];
	//Modes holds the settings each catagory type to be used while loading the audio data
	FMOD_MODE modes[Type_Count];

	void Initialize();

	//Sound Storage
	typedef std::map<std::string, SoundStruct> LoadedSoundMap;
	typedef std::map<std::string, FMOD::Channel*> ChannelMap;

	//Going to need some way to link a gameobject to a sounsource
	//This will mean it will needs its own channel, requiring a channel map
	//Each loaded sound will have a relative channel created of the same name + Channel
	//The component will update the channels position within the components update


	static LoadedSoundMap _loadedSFX;
	static LoadedSoundMap _loadedMusic;
	ChannelMap AllChannels; // Might not need

};