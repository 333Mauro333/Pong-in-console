#ifndef MUSIC_MANAGER_H
#define MUSIC_MANAGER_H

#include <vector>

#include "raylib.h"

#include "enums/music_to_play.h"

using std::vector;


namespace pong_in_console
{
	class MusicManager
	{
	public:
		static void initMusic();
		static void updateMusicStream();
		static void closeMusic();

		static void play(MUSIC_TO_PLAY music);
		static void stop();

	private:
		static vector<Music> musicList;
	};
}

#endif // !MUSIC_MANAGER_H
