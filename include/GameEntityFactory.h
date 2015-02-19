/*******************************************************************//*
 * This class is responsible for the creation of GameEntity objects
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2015-02-07
 * @modified    2015-02-18
 *********************************************************************/
#ifndef SPACESHOOTER_GAMEENTITYFACTORY_H_
    #define SPACESHOOTER_GAMEENTITYFACTORY_H_

#include <map>
#include <string>
#include <vector>

#include "GameEntityData.h"
#include "Level.h" // For SpawnData structure
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
        GameEntity* createEntity(SpawnData data);
        GameEntity* createEntity(EntityXmlStruct xmlStruct);
        void configureEntity(GameEntity* entity, EntityXmlStruct xmlStruct);
        GameEntity* createBackground();
        GameEntity* createEnemyProjectile(GameEntity* enemyEntity);
        GameEntity* createExplosion(GameEntity* destroyedEntity);
        GameEntity* createPlayerProjectile(GameEntity* playerEntity);
        std::vector<GameEntity*> createPlayerInstructions();
        GameEntity* createPlayerInstructionsProjectile(GameEntity* playerEntity);
        GameEntity* createMeteor();
};

// Used alongside stringToEntityEnum to map strings to integers
enum EntityEnum
{
    ENTITY_BACKGROUND,
    ENTITY_ENEMYPROJECTILEHIT,
    ENTITY_ENEMYSTRAIGHT,
    ENTITY_ENEMYCARRIER,
    ENTITY_ENEMYSWOOPLEFT,
    ENTITY_ENEMYSWOOPRIGHT,
    ENTITY_ENEMYZIGZAG,
    ENTITY_PLAYER1,
    ENTITY_PLAYERPROJECTILEHIT,
    ENTITY_SPRITE,
    ENTITY_TEXT,
    ENTITY_UILIVES,
    ENTITY_UIPANEL,
    ENTITY_UISCORE,
};

#endif

