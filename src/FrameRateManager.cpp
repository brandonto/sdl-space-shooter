/*******************************************************************//*
 * Implementation of the FrameRateManager class.
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2014-09-06
 * @modified    2014-09-06
 *********************************************************************/
#include "FrameRateManager.h"

#include <SDL2/SDL.h>

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

