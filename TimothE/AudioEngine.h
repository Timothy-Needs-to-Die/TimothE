
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
	void AudioUpdate(float elapsed);
	void ShutDownAudio();
	void ReleaseSound(FMOD::Sound* sound);
	static void CheckForErrors(FMOD_RESULT result);
	static float RandomBetween(float min, float max);

	//This should be set to whatever position the listener is, either the camera or the player itself
	static void Set3DListenerAttributes(FMOD_VECTOR position, FMOD_VECTOR vel, FMOD_VECTOR forward, FMOD_VECTOR up);

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
	void LoadSound(const char* name, const char* filePath, AudioType type);
	static FMOD::Channel* PlaySound(std::string soundName, float minVolume, float maxVolume, float minPitch, float maxPitch);
	void StopSongs();
	static void TogglePaused(FMOD::Channel* channel);
	static void SetVolume(FMOD::Channel* channel, float value);

	//Audio Modification
	float ChangeOctave(float frequency, float ammount);
	static float ChangeSemitone(float frequency, float ammount);
	void SetPanning(FMOD::Channel* channel, float ammount);
	void SetMasterVolume(float volume);
	void SetSFXVolume(float volume);
	void SetMusicVolume(float volume);
	static enum FadeState { Fade_None, Fade_In, Fade_Out };

private:
	//Test storage
	SoundStruct titleMusic; 

	//Song stuff
	static FMOD::Channel* _currentSongChannel;
	static const char* _currentSongPath;
	SoundStruct _nextSong;

	
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



