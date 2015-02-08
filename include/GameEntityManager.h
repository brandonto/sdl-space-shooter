/*******************************************************************//*
 * This class manages all game entity code. Responsibilities
 * include spawning... TBD
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2014-08-10
 * @modified    2015-02-07
 *********************************************************************/
#ifndef SPACESHOOTER_GAMEENTITYMANAGER_H_
    #define SPACESHOOTER_GAMEENTITYMANAGER_H_

#include <vector>
#include <SDL2/SDL.h>
#include "CollisionManager.h"
#include "GameEntityCollection.h"
#include "GameEntityFactory.h"

class ApplicationState;
class GameEntity;

struct WindowElements;

class GameEntityManager
{
    private:
        CollisionManager collisionManager;
        GameEntityFactory gameEntityFactory;

        GameEntityCollection backgroundLayer;
        GameEntityCollection physicalLayer;
        GameEntityCollection effectLayer;
        GameEntityCollection uiLayer;
        WindowElements* windowElements;

        //bool explosion

    public:
        GameEntityManager(WindowElements* windowElements);

        void onEvent(SDL_Event* event);
        void onUpdate();
        void onRender();

        void pauseAllTimers();
        void resumeAllTimers();

        void addBackgroundEntity(GameEntity* gameEntity);
        void addPhysicalEntity(GameEntity* gameEntity);
        void addEffectEntity(GameEntity* gameEntity);
        void addUIEntity(GameEntity* gameEntity);

        CollisionManager* getCollisionManager();
        GameEntityFactory* getFactory();
};

#endif
