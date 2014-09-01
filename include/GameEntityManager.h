/*******************************************************************//*
 * This class encapsulates all game entity code. Responsibilities
 * include spawning... TBD
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2014-08-10
 * @modified    2014-09-01
 *********************************************************************/
#ifndef SPACESHOOTER_GAMEENTITYMANAGER_H_
    #define SPACESHOOTER_GAMEENTITYMANAGER_H_

#include "GameEntityCollection.h"
#include <vector>
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

        std::vector<GameEntity*> createMainMenu(WindowElements* windowElements);
        GameEntity* createBackground(WindowElements* windowElements);
        void createGameEntityPhysical();

        void createUIElement();
};

#endif
