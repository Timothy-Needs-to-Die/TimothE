#include "AudioEngine.h"
#include "Component.h"
#include "GameObject.h"



class AudioSource : public Component {

public:
	AudioSource();

	COMPONENT_STATIC_TYPE(Sound_Type);

	void Update();
	void PlaySound(std::string soundName, float minVolume, float maxVolume, float minPitch, float maxPitch);
	void TogglePaused();
	void SetVolume(float value);


	FMOD::Channel* _sourceChannel;
	std::string _channelName;

private:

	GameObject* _parentObject;

	bool _isMusicSource;

	glm::vec2 _position;
	float _volume = 1.0f;
};