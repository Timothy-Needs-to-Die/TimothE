
#include "AudioSource.h"

AudioSource::AudioSource(GameObject* parent) : Component(parent)
{

	SetType(Sound_Type);

}

void AudioSource::Update()
{

	_position = _parentObject->GetTransform()->GetPosition();
	FMOD_VECTOR fPos; fPos.x = _position.x; fPos.y = _position.y; fPos.z = 0;

	//Set update channel position to parent object
	_sourceChannel->set3DAttributes(&fPos, 0);


}

void AudioSource::PlaySound(std::string soundName, float minVolume, float maxVolume, float minPitch, float maxPitch)
{
 	_sourceChannel = AudioEngine::PlaySound(soundName, minVolume, maxVolume, minPitch, maxPitch);
}

void AudioSource::TogglePaused()
{
	AudioEngine::TogglePaused(_sourceChannel);
}

void AudioSource::SetVolume(float value)
{
	AudioEngine::SetVolume(_sourceChannel, value);
}

void AudioSource::OnStart()
{
}

void AudioSource::OnUpdate()
{
}

void AudioSource::OnEnd()
{
}

