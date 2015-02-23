/*******************************************************************//*
 * This class is responsible for the creation of GameEntity objects
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2015-02-07
 * @modified    2015-02-23
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
class Vector2D;

struct WindowElements;

class GameEntityFactory
{
    private:
        GameEntityData gameEntityData;
        GameEntityManager* gameEntityManager;
        WindowElements* windowElements;

        // Used alongside EntityEnum to map strings to integers
        std::map<std::string, int> stringToEntityEnum;

        Vector2D* playerPosition;

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
        GameEntity* createEntityByName(std::string name);
        GameEntity* createEntity(SpawnData data);
        GameEntity* createEntity(EntityXmlStruct xmlStruct);
        void configureEntity(GameEntity* entity, EntityXmlStruct xmlStruct);
        GameEntity* createBackground();
        std::vector<GameEntity*> createPlayerInstructions();
        GameEntity* createMeteor();

        Vector2D getPlayerPosition();
};

// Used alongside stringToEntityEnum to map strings to integers
enum EntityEnum
{
    ENTITY_BACKGROUND,
    ENTITY_ENEMYBOSS,
    ENTITY_ENEMYPROJECTILE,
    ENTITY_ENEMYPROJECTILEHIT,
    ENTITY_ENEMYSTRAIGHT,
    ENTITY_ENEMYCARRIER,
    ENTITY_ENEMYSWOOPLEFT,
    ENTITY_ENEMYSWOOPRIGHT,
    ENTITY_ENEMYUFO,
    ENTITY_ENEMYZIGZAG,
    ENTITY_EXPLOSION,
    ENTITY_PLAYER1,
    ENTITY_PLAYERINSTRUCTIONSPROJECTILE,
    ENTITY_PLAYERPROJECTILE,
    ENTITY_PLAYERPROJECTILEHIT,
    ENTITY_SPRITE,
    ENTITY_TEXT,
    ENTITY_UILIVES,
    ENTITY_UIPANEL,
    ENTITY_UISCORE,
};

#endif

