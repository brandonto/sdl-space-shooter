/*******************************************************************//*
 * Implementation of the FrameRateManager class.
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2014-09-06
 * @modified    2015-02-19
 *********************************************************************/
#include "FrameRateManager.h"

#ifdef _WIN32
	#include <SDL.h>
#endif

#ifdef __linux
	#include <SDL2/SDL.h>
#endif

FrameRateManager::FrameRateManager()
:   fps(DEFAULT_FRAMES_PER_SECOND)
{

}

void FrameRateManager::beginFrame()
{
    fpsTimer.start();
}

void FrameRateManager::endFrame()
{
    int time = fpsTimer.getTimeOnTimer();
    if (time < 1000/fps)
    {
        SDL_Delay(1000/fps - time);
    }
    fpsTimer.stop();
}

void FrameRateManager::setFPS(int fps)
{
    this->fps = fps;
}

