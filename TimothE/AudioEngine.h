#include <fmod.hpp>
#include <string>
#include <map>

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

	// == Core Functionality == // 
	FMOD::Sound* LoadAudio(const char* filePath);
	FMOD::Sound* CreateAudioStream(const char* filePath);

	void PlayOneShot(FMOD::Sound*);

private:

	FMOD::System* _fmodSystem;
	void Initialize();

};

