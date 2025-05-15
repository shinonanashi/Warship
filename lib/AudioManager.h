#pragma once
#include <SDL_mixer.h>

class AudioManager
{
public:
	AudioManager();

	static AudioManager& GetInstance();

	void Init();
	void LoadSoundEffectsAndMusic();
	void PlaySoundEffect(Mix_Chunk* p_SoundEffect);
	void PlayMusic(Mix_Music* p_Music);
	void SetVolume(Mix_Chunk* p_SoundEffect, int p_Volume);

	Mix_Music* m_Music;

	Mix_Chunk* m_Button;
	Mix_Chunk* m_BulletCollision;
	Mix_Chunk* m_Shoot;
	Mix_Chunk* m_Explosion;
	Mix_Chunk* m_FirstAid;
	Mix_Chunk* m_Shield;
	Mix_Chunk* m_Missile;
	Mix_Chunk* m_Flares;
	Mix_Chunk* m_MissileReady;
	Mix_Chunk* m_FlaresReady;
};
