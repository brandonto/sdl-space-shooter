/*******************************************************************//*
 * This class manages the collision detection of all game entities.
 * The game object must be added to the collision manager collection.
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2014-09-18
 * @modified    2015-02-19
 *********************************************************************/
#ifndef SPACESHOOTER_COLLISIONMANAGER_
    #define SPACESHOOTER_COLLISIONMANAGER_

#include <vector>

#ifdef _WIN32
	#include <SDL.h>
#endif

#ifdef __linux
	#include <SDL2/SDL.h>
#endif

#include "Vector2D.h"

//NOT COMPLETE

class GameEntity;
class GameEntityManager;

struct WindowElements;

class CollisionManager
{
    private:
        WindowElements* windowElements;
        std::vector<GameEntity*> friendlyArray;
        std::vector<GameEntity*> neutralArray;
        std::vector<GameEntity*> enemyArray;

        bool checkCollisionAgainstFriendly(GameEntity* gameEntity);
        bool checkCollisionAgainstNeutral(GameEntity* gameEntity);
        bool checkCollisionAgainstEnemy(GameEntity* gameEntity);
        bool checkCollisionBoundingRect(GameEntity* checkSource,
                                        GameEntity* checkDest);

    public:
        //Constructor
        CollisionManager(WindowElements* windowElements);

        //Destructor
        ~CollisionManager();

        //Methods
        //The flag represents the group of entity that the game onject belongs to
        void addCollisionObject(GameEntity* gameEntity, int flag);
        void deleteCollisionObject(GameEntity* gameEntity, int flag);

        //The flags represent the group of entities to check for collisions against
        bool checkCollision(GameEntity* gameEntity, int flags);
};

enum CollisionFlags
{
    ENTITY_FRIENDLY     = 0x01,
    ENTITY_NEUTRAL      = 0x02,
    ENTITY_ENEMY        = 0x04,
};

#endif
