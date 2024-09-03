#include "music_manager.h"


namespace pong_in_console
{
	Music MusicManager::musicList[MusicManager::amountOfMusics] = {};

	void MusicManager::initMusic()
	{
		InitAudioDevice();

		musicList[0] = LoadMusicStream("res/audio/music/mechanical.mp3");
	}
	void MusicManager::updateMusicStream()
	{
		for (int i = 0; i < amountOfMusics; i++)
		{
			UpdateMusicStream(musicList[i]);
		}
	}
	void MusicManager::closeMusicSistem()
	{
		for (int i = 0; i < amountOfMusics; i++)
		{
			UnloadMusicStream(musicList[i]);
		}

		CloseAudioDevice();
	}

	void MusicManager::play(MUSIC_TO_PLAY music)
	{
		PlayMusicStream(musicList[(int)music]);
	}
	void MusicManager::stop()
	{
		for (int i = 0; i < amountOfMusics; i++)
		{
			StopMusicStream(musicList[i]);
		}
	}
}
