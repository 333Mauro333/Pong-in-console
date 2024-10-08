#ifndef MUSIC_MANAGER_H
#define MUSIC_MANAGER_H

#include "raylib.h"

#include "enums/music_to_play.h"


namespace pong_in_console
{
	class MusicManager
	{
	public:
		static void initMusicSystem();
		static void updateMusicStream();
		static void closeMusicSystem();

		static void play(MUSIC_TO_PLAY music);
		static void stop();

	private:
		static const int amountOfMusics = 1;
		static Music musicList[amountOfMusics];
		static int actualMusicPosition;
	};
}

#endif // !MUSIC_MANAGER_H
