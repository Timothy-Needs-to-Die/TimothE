#include "AudioEngine.h"
#include <iostream>

AudioEngine::AudioEngine()
{
	//Create and initiliaze the fmod core system
	FMOD::System_Create(&_fmodSystem);
	Initialize();
}

//This must be called within the main game loop in order for FMOD 
//features to work correctly
void AudioEngine::AudioUpdate()
{
	_fmodSystem->update();
}

//Shut down the audio system. 
//This should be done on the ending of the program.
void AudioEngine::ShutDownAudio()
{
	_fmodSystem->release();
}

//Release the sound object from memory. 
//This should be done when a sound object is no longer going to be used.
void AudioEngine::ReleaseSound(FMOD::Sound* sound)
{
	sound->release();
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

//CreateAndLoad loads a sound file into memory and returns that to the call
//Loading sounds into memory is ideal for most ingame sounds as they will be used multiple times
FMOD::Sound* AudioEngine::LoadAudio( const char* filePath)
{
	FMOD::Sound* soundToLoad;
	FMOD_RESULT result = _fmodSystem->createSound(filePath, FMOD_DEFAULT, 0, &soundToLoad);
	CheckForErrors(result);
	return soundToLoad;
}

//Creates an audio stream.
//Audio streams are ideal for streaming long audio files such as soundtracks or voicelines
//As it is not as necaserry to load these into memory. 
FMOD::Sound* AudioEngine::CreateAudioStream( const char* filePath)
{
	FMOD::Sound* soundToStream;;
	FMOD_RESULT result = _fmodSystem->createStream(filePath, FMOD_DEFAULT, 0, &soundToStream);
	CheckForErrors(result);
	return soundToStream;
}

//This play sound method is useful for simple one shot sounds that do not need any modification 
void AudioEngine::PlayOneShot(FMOD::Sound* sound)
{
	FMOD_RESULT result = _fmodSystem->playSound(sound, NULL, false, 0);
	CheckForErrors(result);
}

//Initialize the fmod audio system.
// the first parameter represents the total audio channels that will be created. 
void AudioEngine::Initialize()
{

	FMOD_RESULT result = _fmodSystem->init(50, FMOD_INIT_NORMAL, 0);
	CheckForErrors(result);
}
