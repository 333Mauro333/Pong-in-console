#ifndef TIMER_H
#define TIMER_H

namespace pong_in_console
{
	class Timer
	{
	public:
		Timer();
		~Timer();

		void startCounting();
		void updateTime();
		void stopCounting();

		int getActualTime();
		bool getTheTimeBeganToCount();

	private:
		long long startTimeReference;
		long long elapsedTime;
		bool theTimeBeganToCount;

		void saveStartTimeReference();

		void saveElapsedTime();
		long long getElapsedTime();
		long long getTimeInThisFrame();
		void convertElapsedTimeToSeconds();
	};
}

#endif // !TIMER_H
