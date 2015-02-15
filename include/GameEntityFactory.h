/*******************************************************************//*
 * This class is responsible for the creation of GameEntity objects
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2015-02-07
 * @modified    2015-02-12
 *********************************************************************/
#ifndef SPACESHOOTER_GAMEENTITYFACTORY_H_
    #define SPACESHOOTER_GAMEENTITYFACTORY_H_

#include <map>
#include <string>
#include <vector>

#include "GameEntityData.h"
#include "StateEntityParser.h" // For EntityXmlStruct structure

class ApplicationState;
class GameEntity;
class GameEntityManager;

struct WindowElements;

class GameEntityFactory
{
    private:
        GameEntityData gameEntityData;
        GameEntityManager* gameEntityManager;
        WindowElements* windowElements;

        // Used alongside EntityEnum to map strings to integers
        std::map<std::string, int> stringToEntityEnum;

    public:
        //Constructor
        GameEntityFactory(GameEntityManager* gameEntityManager,
                            WindowElements* windowElements);

        //Destructor
        ~GameEntityFactory();

        //Methods
        std::vector<GameEntity*> createBackgroundEntities();
        std::vector<GameEntity*> createPhysicalEntities();
        std::vector<GameEntity*> createEffectEntities();
        std::vector<GameEntity*> createUIEntities();
        GameEntity* createEntity(std::string type);
        GameEntity* createEntity(EntityXmlStruct xmlStruct);
        void configureEntity(GameEntity* entity, EntityXmlStruct xmlStruct);
        GameEntity* createBackground();
        GameEntity* createEnemy();
        GameEntity* createEnemyProjectile(GameEntity* enemyEntity);
        std::vector<GameEntity*> createEnemyWaveStraight2();
        std::vector<GameEntity*> createEnemyWaveStraight3();
        GameEntity* createExplosion(GameEntity* destroyedEntity);
        GameEntity* createPlayer();
        GameEntity* createPlayerProjectile(GameEntity* playerEntity);
        std::vector<GameEntity*> createPlayerInstructions();
        GameEntity* createPlayerInstructionsProjectile(GameEntity* playerEntity);
        GameEntity* createMeteor();
};

// Used alongside stringToEntityEnum to map strings to integers
enum EntityEnum
{
    ENTITY_BACKGROUND,
    ENTITY_ENEMYSTRAIGHT,
    ENTITY_ENEMYZIGZAG,
    ENTITY_PLAYER,
    ENTITY_SPRITE,
    ENTITY_TEXT,
    ENTITY_UIPANEL,
};

#endif

