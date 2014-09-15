/*******************************************************************//*
 * This class is a wrapper for the collection of GameEntity objects
 * used in the game. Also acts as a pseudo-contract for the collection
 * used.
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2014-08-10
 * @modified    2014-09-06
 *********************************************************************/
#ifndef SPACESHOOTER_GAMEENTITYCOLLECTION_H_
    #define SPACESHOOTER_GAMEENTITYCOLLECTION_H_

#include <list>

class GameEntity;

union SDL_Event;

class GameEntityCollection
{
    private:
        std::list<GameEntity*> collection;

    public:
        //Constructor
        GameEntityCollection();

        //Destructor
        ~GameEntityCollection();

        //Methods
        void add(GameEntity* gameEntity);
        void remove(GameEntity* gameEntity);
        void onEvent(SDL_Event* event);
        void onUpdate();
        void onRender();
        void onPauseTimers();
        void onResumeTimers();
};

#endif
