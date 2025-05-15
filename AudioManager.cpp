

#include "lib/AudioManager.h"
#include <iostream>


AudioManager::AudioManager()
{

}

AudioManager& AudioManager::GetInstance()
{
	static AudioManager* instance = new AudioManager;

	return *instance;
}

void AudioManager::Init()
{
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
		std::cout << "SDL_mixer could not initialize!";

	LoadSoundEffectsAndMusic();

	PlayMusic(m_Music);
}

void AudioManager::LoadSoundEffectsAndMusic()
{
	m_Music = Mix_LoadMUS("res/Sounds/Music.mp3");

	m_Button = Mix_LoadWAV("res/Sounds/Button.wav");
	m_BulletCollision = Mix_LoadWAV("res/Sounds/BulletCollision.wav");
	m_Shoot = Mix_LoadWAV("res/Sounds/Shoot.wav");
	m_Explosion = Mix_LoadWAV("res/Sounds/Explosion.wav");
	m_Shield = Mix_LoadWAV("res/Sounds/Shield.wav");
	m_FirstAid = Mix_LoadWAV("res/Sounds/FirstAid.wav");
	m_Missile = Mix_LoadWAV("res/Sounds/Missile.wav");
	m_Flares = Mix_LoadWAV("res/Sounds/Flares.wav");
	m_MissileReady = Mix_LoadWAV("res/Sounds/MissileReady.wav");
	m_FlaresReady = Mix_LoadWAV("res/Sounds/FlaresReady.wav");


	SetVolume(m_Shoot, 10);
	SetVolume(m_BulletCollision, 10);
	SetVolume(m_Flares, 20);
	SetVolume(m_MissileReady, 10);
	SetVolume(m_FlaresReady, 10);
	SetVolume(m_Missile, 50);
	SetVolume(m_FirstAid, 75);
	SetVolume(m_Shield, 75);
}

void AudioManager::PlaySoundEffect(Mix_Chunk* p_SoundEffect)
{
	Mix_PlayChannel(-1, p_SoundEffect, 0);
}

void AudioManager::PlayMusic(Mix_Music* p_Music)
{
	if (Mix_PlayingMusic() == 0)
		Mix_PlayMusic(p_Music, -1);
}

void AudioManager::SetVolume(Mix_Chunk* p_SoundEffect, int m_Volume)
{
	p_SoundEffect->volume = (MIX_MAX_VOLUME * m_Volume) / 100;
}
