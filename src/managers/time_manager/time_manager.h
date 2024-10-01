#ifndef TIME_MANAGER_H
#define TIME_MANAGER_H

namespace pong_in_console
{
	class TimeManager
	{
	public:
		static void startCounting();
		static void updateTime();
		static void stopCounting();

		static int getActualTime();
		static bool getTheTimeBeganToCount();

	private:
		static long long startTimeReference;
		static long long elapsedTime;
		static bool theTimeBeganToCount;

		static void saveStartTimeReference();

		static void saveElapsedTime();
		static long long getElapsedTime();
		static long long getTimeInThisFrame();
		static void convertElapsedTimeToSeconds();
	};
}

#endif // !TIME_MANAGER_H
