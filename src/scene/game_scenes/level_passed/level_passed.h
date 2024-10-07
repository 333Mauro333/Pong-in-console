#ifndef LEVEL_PASSED_H
#define LEVEL_PASSED_H

#include "scene/scene.h"


namespace pong_in_console
{
	class LevelPassed : public Scene
	{
	public:
		LevelPassed();
		~LevelPassed();

		void inputUpdate(int key) override;
		void update() override;
		void erase() override;
		void draw() override;

	private:
		bool itWasDrawn;
		int time;
		int pointsForBlockDestruction;
		int pointsForTime;
		int pointsEarned;
		int totalPoints;

		const int textsColumn = 30;
		const int numbersColumn = 85;

		void drawFrames();

		void writePointsForBlockDestruction(int y);
		void writePointsForTime(int y);
		void writePointsEarned(int y);
		void writeTotalPoints(int y);

		void initPointsForTime();
	};
}

#endif // !LEVEL_PASSED_H
