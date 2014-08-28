/*******************************************************************//*
 * This class encapsulates all game entity code. Responsibilities
 * include spawning... TBD
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2014-08-10
 * @modified    2014-08-27
 *********************************************************************/
#ifndef SPACESHOOTER_GAMEENTITYMANAGER_H_
    #define SPACESHOOTER_GAMEENTITYMANAGER_H_

#include "GameEntityCollection.h"
#include <SDL2/SDL.h>

struct WindowElements;

class GameEntityManager
{
    private:
        GameEntityCollection backgroundLayer;
        GameEntityCollection physicalLayer;
        GameEntityCollection uiLayer;

    public:
        GameEntityManager();

        void onEvent(SDL_Event event);
        void onUpdate();
        void onRender();

        void createBackground(WindowElements* windowElements);
        void createGameEntityPhysical();
        void createUIElement();
};

#endif
