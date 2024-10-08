#include "music_manager.h"


namespace pong_in_console
{
	Music MusicManager::musicList[MusicManager::amountOfMusics] = {};
	int MusicManager::actualMusicPosition = 0;

	void MusicManager::initMusicSystem()
	{
		InitAudioDevice();

		musicList[0] = LoadMusicStream("res/audio/music/mechanical.mp3");
	}
	void MusicManager::updateMusicStream()
	{
		UpdateMusicStream(musicList[actualMusicPosition]);
	}
	void MusicManager::closeMusicSystem()
	{
		stop();

		for (int i = 0; i < amountOfMusics; i++)
		{
			UnloadMusicStream(musicList[i]);
		}

		CloseAudioDevice();
	}

	void MusicManager::play(MUSIC_TO_PLAY music)
	{
		stop();

		actualMusicPosition = (int)music;

		PlayMusicStream(musicList[actualMusicPosition]);
	}
	void MusicManager::stop()
	{
		StopMusicStream(musicList[actualMusicPosition]);
	}
}
