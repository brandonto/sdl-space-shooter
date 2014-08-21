/*******************************************************************//*
 * This class encapsulates all game entity code. Responsibilities
 * include spawning... TBD
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2014-08-10
 * @modified    2014-08-20
 *********************************************************************/
#ifndef SPACESHOOTER_GAMEENTITYMANAGER_H_
    #define SPACESHOOTER_GAMEENTITYMANAGER_H_

#include "GameEntityCollection.h"
#include <SDL2/SDL.h>

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

        void createBackground(SDL_Renderer* renderer);
        void createGameEntityPhysical();
        void createUIElement();
};

#endif
