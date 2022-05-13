#include "AudioEngine.h"



FMOD::Channel* AudioEngine::_currentSongChannel = 0;
const char* AudioEngine::_currentSongPath = 0;
AudioEngine::FadeState AudioEngine::fade;
FMOD::System* AudioEngine::_fmodSystem;
FMOD::ChannelGroup* AudioEngine::_master;
FMOD::ChannelGroup* AudioEngine::_groups[Type_Count];
AudioEngine::LoadedSoundMap AudioEngine::_loadedSFX;
AudioEngine::LoadedSoundMap AudioEngine::_loadedMusic;
SoundStruct AudioEngine::_nextSong;

// ============================== System Functions =============================== // 
AudioEngine::AudioEngine()
{
	//Create and initiliaze the fmod core system
	FMOD::System_Create(&_fmodSystem);

	FMOD_RESULT result;
	result = _fmodSystem->init(50, FMOD_INIT_NORMAL, 0);
	CheckForErrors(result);

	//Create channels for each audio type
	_fmodSystem->getMasterChannelGroup(&_master);
	for (int i = 0; i < Type_Count; i++)
	{
		_fmodSystem->createChannelGroup(0, &_groups[i]);
		_master->addGroup(_groups[i]);
	}
	//Set up modes for each type
	modes[Type_SFX] = FMOD_DEFAULT;
	modes[Type_Song] = FMOD_DEFAULT | FMOD_CREATESTREAM | FMOD_LOOP_NORMAL;

	_currentSongChannel = nullptr;


}

AudioEngine::~AudioEngine()
{
	//Release remaining sounds


}

//Initialize the fmod audio system.
// the first parameter represents the total audio channels that will be created. 
void AudioEngine::Initialize()
{


}

//This must be called within the main game loop in order for FMOD 
//features to work correctly
void AudioEngine::AudioUpdate(float elapsed)
{
	_fmodSystem->update();

	//Fade in/out processing
	const float fadeTime = 1.0f; // Seconds
	if (_currentSongChannel != 0 && fade == Fade_In) {
		float volume;
		_currentSongChannel->getVolume(&volume);
		float nextVolume = volume + elapsed / fadeTime;
		if (nextVolume >= 1.0f)
		{
			_currentSongChannel->setVolume(1.0f);
			fade = Fade_None;
		}
		else
			_currentSongChannel->setVolume(nextVolume);
	}
	else if (_currentSongChannel != 0 && fade == Fade_Out) {
		float volume;
		_currentSongChannel->getVolume(&volume);
		float nextVolume = volume - elapsed / fadeTime;
		if (nextVolume <= 0.0f)
		{
			_currentSongChannel->stop();
			_currentSongChannel = 0;
			_currentSongPath = nullptr;
			fade = Fade_None;
		}
		else
			_currentSongChannel->setVolume(nextVolume);
	}
	/*else if (_currentSongChannel == 0 && !_nextSong.filePath == 0 ) {
		PlaySound(_nextSong);
		_nextSong.filePath = 0;
	}*/



}

//Shut down the audio system. 
//This should be done on the ending of the program.
void AudioEngine::ShutDownAudio()
{
	_fmodSystem->release();
}

//If an error was detected with a certain issue this will print an error string
//to aid with debugging
void AudioEngine::CheckForErrors(FMOD_RESULT result)

{
	if (result != FMOD_OK)
	{
		std::cout << "Audio Engine Error: ";
		std::cout << result << std::endl;
	}
}

//Release the sound object from memory. 
//This should be done when a sound object is no longer going to be used.
void AudioEngine::ReleaseSound(FMOD::Sound* sound)
{
	sound->release();
}

float AudioEngine::RandomBetween(float min, float max) {
	if (min == max) return min;
	float n = (float)rand() / (float)RAND_MAX;
	return min + n * (max - min);
}

void AudioEngine::Set3DListenerAttributes(FMOD_VECTOR position, FMOD_VECTOR vel, FMOD_VECTOR forward, FMOD_VECTOR up)
{
	_fmodSystem->set3DListenerAttributes(0, &position, &vel, &forward, &up);
}

// ================================================================================ //

// ========================= Grouping and Group Controls ========================== // 
// 
//Creates an audio channell group
//This is useful for grouping together relevant audio channels such as
// music, sfx, master etc.
FMOD::ChannelGroup* AudioEngine::CreateChanellGroup(const char* name) {
	FMOD::ChannelGroup* newChanellGroup;

	FMOD_RESULT result;
	result = _fmodSystem->createChannelGroup(name, &newChanellGroup);
	CheckForErrors(result);
	return newChanellGroup;
}

//Set a certain channel to a channel group
void AudioEngine::SetChannelGroup(FMOD::Channel* channelToSet, FMOD::ChannelGroup* groupToSet) {
	FMOD_RESULT result;
	result = channelToSet->setChannelGroup(groupToSet);
	CheckForErrors(result);
}

//Add a group as a child group of another group, creating a hierarchy.
//This should be used to create a 'Master' Group which is the parent of every group
void AudioEngine::AddChildGroup(FMOD::ChannelGroup* parentGroup, FMOD::ChannelGroup* childGroup) {
	FMOD_RESULT result = parentGroup->addGroup(childGroup);
	//CheckForErrors(result);
}

//Gets the master group, the master group object should be passed in.
FMOD::ChannelGroup* AudioEngine::GetMasterGroup(FMOD::ChannelGroup* masterGroupObject) {

	FMOD::ChannelGroup* masterGroup = masterGroupObject;
	//FMOD_RESULT result = _fmodSystem->getMasterChannelGroup(&masterGroup);
	//CheckForErrors(_fmodSystem->getMasterChannelGroup(&masterGroup));

	return masterGroup;
}

//========================= Group Controls ========================= //

void AudioEngine::StopGroup(FMOD::ChannelGroup* group) {
	FMOD_RESULT result = group->stop();
	CheckForErrors(result);
}

void AudioEngine::ToggleGroupMute(FMOD::ChannelGroup* group) {
	bool muted;

	group->getMute(&muted);
	FMOD_RESULT result = group->setMute(!muted);
	CheckForErrors(result);
}

void AudioEngine::ToggleGroupPause(FMOD::ChannelGroup* group) {
	bool paused;
	group->getPaused(&paused);
	FMOD_RESULT result = group->setPaused(!paused);
	CheckForErrors(result);
}

void AudioEngine::SetGroupVolume(FMOD::ChannelGroup* group, float value) {
	FMOD_RESULT result = group->setVolume(value);
	CheckForErrors(result);
}

//Set pitch works differently with groups, it instead takes in a value between 0 and 10
//and multiplies the number by its current frequency
void AudioEngine::SetGroupPitch(FMOD::ChannelGroup* group, float value) {
	FMOD_RESULT result = group->setPitch(value);
	CheckForErrors(result);
}

// ================================================================================ //

// ============================== Core Functionality ============================== // 
//CreateAndLoad loads a sound file into memory and populates the '_sounds' map with the sound data
//Loading sounds into memory is ideal for most ingame sounds as they will be used multiple times
//void AudioEngine::Load(AudioType type, const char* filePath)


void AudioEngine::LoadSound(const char* name, const char* filePath, AudioType type)
{
	SoundStruct newSound = SoundStruct();
	newSound.name = name;
	newSound.filePath = filePath;
	newSound.type = type;

	FMOD::Sound* soundToLoad;

	FMOD_RESULT result = _fmodSystem->createSound(newSound.filePath, FMOD_DEFAULT, 0, &soundToLoad);
	newSound.sound = soundToLoad;

	CheckForErrors(result);
	std::cout << "Sound Loaded: " << newSound.name << std::endl;
	if (type == AudioType::Type_SFX) {
		_loadedSFX[newSound.name] = newSound;
	}
	else
		_loadedMusic[newSound.name] = newSound;
}


//Creates an audio stream.
//Audio streams are ideal for streaming long audio files such as soundtracks or voicelines
//As it is not as necaserry to load these into memory. 
FMOD::Sound* AudioEngine::CreateAudioStream(const char* filePath)
{
	FMOD::Sound* soundToStream;;
	FMOD_RESULT result = _fmodSystem->createStream(filePath, FMOD_DEFAULT, 0, &soundToStream);
	CheckForErrors(result);
	return soundToStream;
}


//Play sound effects
//Pass in values for min and max pitch to allow for slight variations in pitch for repeating sounds (footsteps, attacks etc)
FMOD::Channel* AudioEngine::PlaySound(std::string soundName, float minVolume, float maxVolume, float minPitch, float maxPitch)
{
	auto sound = _loadedSFX.find(soundName);
	if (sound == _loadedSFX.end()) {
		std::cout << "Sound not found in loaded sounds" << std::endl;
		return 0;
	}

	if (sound->second.type == AudioType::Type_SFX) {
		//Calculate random value between pitch in the desired range
		float volume = RandomBetween(minVolume, maxVolume);
		float pitch = RandomBetween(minPitch, maxPitch);

		//Play the sound effects while applying values to the channel 
		FMOD::Channel* channel;
		_fmodSystem->playSound(sound->second.sound, NULL, false, &channel);
		channel->setChannelGroup(_groups[Type_SFX]);
		channel->setVolume(volume);
		float frequency;
		channel->getFrequency(&frequency);
		channel->setFrequency(ChangeSemitone(frequency, pitch));
		channel->setPaused(false);
		return channel;
	}
	else if (sound->second.type == AudioType::Type_Song) {
		//Start playing song with volume set to 0 then fade in 

		FMOD::Channel* channel;
		FMOD_RESULT result = _fmodSystem->playSound(sound->second.sound, _groups[Type_Song], false, &channel);
		std::cout << "PlaySong";
		CheckForErrors(result);
		_currentSongChannel->setChannelGroup(_groups[Type_Song]);
		_currentSongChannel->setVolume(0.0f);
		fade = Fade_In;


		return channel;
	}

}


void AudioEngine::StopSongs()
{
	if (_currentSongChannel != 0)
	{
		fade = Fade_Out;

	}
	_nextSong.filePath = nullptr;
}

//Toggle pause on a currently running audio channel 
void AudioEngine::TogglePaused(FMOD::Channel* channel)
{
	bool paused;
	channel->getPaused(&paused);
	channel->setPaused(!paused);
}

void AudioEngine::SetVolume(FMOD::Channel* channel, float value)
{
	channel->setVolume(value);

}

// ================================================================================ //
// ============================== Audio Modification ============================== // 

// Adjust the octave or frequency of a sound 
// To Utilise these methods first get the frequency of the channel you wish to modify and store it as a float
// Then create a new float 'newFrequency' variable and set it equal to a function call to either method, passing in
// frequency and the required change of value
float AudioEngine::ChangeOctave(float frequency, float ammount) {
	static float octaveRatio = 2.0f;
	return frequency * pow(octaveRatio, ammount);
}

float AudioEngine::ChangeSemitone(float frequency, float ammount) {
	static float semitoneRatio = pow(2.0f, 1.0f / 12.0f);
	return frequency * pow(semitoneRatio, ammount);
}

//Set the panning of the channel (Left/right)
//								   (-1/1)
void AudioEngine::SetPanning(FMOD::Channel* channel, float ammount) {

	channel->setPan(ammount);
}

void AudioEngine::SetMasterVolume(float volume)
{
	_master->setVolume(volume);
}

void AudioEngine::SetSFXVolume(float volume)
{
	_groups[Type_SFX]->setVolume(volume);
}

void AudioEngine::SetMusicVolume(float volume)
{
	_groups[Type_Song]->setVolume(volume);
}
