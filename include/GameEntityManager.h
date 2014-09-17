/*******************************************************************//*
 * This class encapsulates all game entity code. Responsibilities
 * include spawning... TBD
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2014-08-10
 * @modified    2014-09-17
 *********************************************************************/
#ifndef SPACESHOOTER_GAMEENTITYMANAGER_H_
    #define SPACESHOOTER_GAMEENTITYMANAGER_H_

#include "GameEntityCollection.h"
#include <vector>
#include <SDL2/SDL.h>

class ApplicationState;
class GameEntity;

struct WindowElements;

class GameEntityManager
{
    private:
        GameEntityCollection backgroundLayer;
        GameEntityCollection physicalLayer;
        GameEntityCollection uiLayer;
        WindowElements* windowElements;

    public:
        GameEntityManager(WindowElements* windowElements);

        void onEvent(SDL_Event* event);
        void onUpdate();
        void onRender();

        void pauseAllTimers();
        void resumeAllTimers();

        std::vector<GameEntity*> createMainMenu(ApplicationState* state);
        GameEntity* createBackground();
        GameEntity* createEnemy();
        GameEntity* createEnemyProjectile(GameEntity* enemyEntity);
        std::vector<GameEntity*> createEnemyWaveStraight();
        GameEntity* createPlayer();
        GameEntity* createPlayerProjectile(GameEntity* playerEntity);
        GameEntity* createMeteor();
};

#endif
