/*******************************************************************//*
 * This class is responsible for the creation of GameEntity objects
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2015-02-07
 * @modified    2015-02-07
 *********************************************************************/
#ifndef SPACESHOOTER_GAMEENTITYFACTORY_H_
    #define SPACESHOOTER_GAMEENTITYFACTORY_H_

#include <string>
#include <vector>

#include "StateEntityParser.h"

class ApplicationState;
class GameEntity;
class GameEntityManager;

struct WindowElements;

class GameEntityFactory
{
    private:
        StateEntityParser xmlParser;
        GameEntityManager* gameEntityManager;
        WindowElements* windowElements;

    public:
        //Constructor
        GameEntityFactory(GameEntityManager* gameEntityManager,
                            WindowElements* windowElements);

        //Destructor
        ~GameEntityFactory();

        //Methods
        std::vector<GameEntity*> createUIEntities();
        std::vector<GameEntity*> createMainMenu(ApplicationState* state);
        std::vector<GameEntity*> createUIInstructions(ApplicationState* state);
        std::vector<GameEntity*> createUICredits(ApplicationState* state);
        std::vector<GameEntity*> createGameMenu(ApplicationState* state);
        GameEntity* createBackground();
        GameEntity* createEnemy();
        GameEntity* createEnemyProjectile(GameEntity* enemyEntity);
        std::vector<GameEntity*> createEnemyWaveStraight2();
        std::vector<GameEntity*> createEnemyWaveStraight3();
        GameEntity* createExplosion(GameEntity* destroyedEntity);
        GameEntity* createPlayer();
        GameEntity* createPlayerProjectile(GameEntity* playerEntity);
        GameEntity* createPlayerInstructions();
        GameEntity* createPlayerInstructionsProjectile(GameEntity* playerEntity);
        GameEntity* createMeteor();
};

#endif

