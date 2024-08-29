#include "music_manager.h"


namespace pong_in_console
{
	vector<Music> MusicManager::musicList = vector<Music>();

	void MusicManager::initMusic()
	{
		InitAudioDevice();

		musicList.push_back( LoadMusicStream("res/audio/music/mechanical.mp3") );
	}
	void MusicManager::updateMusicStream()
	{
		for (int i = 0; i < musicList.size(); i++)
		{
			UpdateMusicStream(musicList[i]);
		}
	}
	void MusicManager::closeMusic()
	{
		for (int i = 0; i < musicList.size(); i++)
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
		for (int i = 0; i < musicList.size(); i++)
		{
			StopMusicStream(musicList[i]);
		}
	}
}
