/*******************************************************************//*
 * This class encapsulates the functionality of a timer/stopwatch.
 * Used for spawning, fps capping, etc.
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2014-09-06
 * @modified    2014-09-06
 *********************************************************************/
#ifndef SPACESHOOTER_TIMER_H_
    #define SPACESHOOTER_TIMER_H_

#ifdef _WIN32
	#include <SDL.h>
#endif
#ifdef linux
	#include <SDL2/SDL.h>
#endif


class Timer
{
    private:
		Uint32 startTime;
        Uint32 tempTime;
		Uint32 pausedTime;

		bool started;
		bool paused;

    public:
        //Constructor
		Timer();

		//Methods
		void start();
		void stop();
		void pause();
		void resume();
		Uint32 getTimeOnTimer();
		Uint32 getTimeSinceTimerStarted();
		bool isStarted();
		bool isPaused();

};

#endif
