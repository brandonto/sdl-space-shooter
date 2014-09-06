/*******************************************************************//*
 * This class encapsulates the logic for controlling frame rate
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2014-09-06
 * @modified    2014-09-06
 *********************************************************************/
#ifndef SPACESHOOTER_FRAMERATEMANAGER_H_
    #define SPACESHOOTER_FRAMERATEMANAGER_H_

#include "Timer.h"

class FrameRateManager
{
    private:
		Timer fpsTimer;
        const int DEFAULT_FRAMES_PER_SECOND = 60;
        int fps;

    public:
        //Constructor
		FrameRateManager();

		//Methods
        void beginFrame();
        void endFrame();
        void setFPS(int fps);
};

#endif
