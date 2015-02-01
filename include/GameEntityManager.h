/*******************************************************************//*
 * This class encapsulates all game entity code. Responsibilities
 * include spawning... TBD
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2014-08-10
 * @modified    2015-02-01
 *********************************************************************/
#ifndef SPACESHOOTER_GAMEENTITYMANAGER_H_
    #define SPACESHOOTER_GAMEENTITYMANAGER_H_

#include <vector>
#include <SDL2/SDL.h>
#include "CollisionManager.h"
#include "GameEntityCollection.h"

class ApplicationState;
class GameEntity;

struct WindowElements;

class GameEntityManager
{
    private:
        CollisionManager collisionManager;

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

        std::vector<GameEntity*> createMainMenu(ApplicationState* state);
        std::vector<GameEntity*> createUIInstructions(ApplicationState* state);
        std::vector<GameEntity*> createUICredits(ApplicationState* state);
        GameEntity* createBackground();
        GameEntity* createEnemy();
        GameEntity* createEnemyProjectile(GameEntity* enemyEntity);
        std::vector<GameEntity*> createEnemyWaveStraight2();
        std::vector<GameEntity*> createEnemyWaveStraight3();
        GameEntity* createExplosion(GameEntity* destroyedEntity);
        GameEntity* createPlayer();
        GameEntity* createPlayerProjectile(GameEntity* playerEntity);
        GameEntity* createMeteor();
};

#endif
