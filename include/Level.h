/*******************************************************************//*
 * This is the Level class for the game. This class keeps track of
 * level specific data like enemy spawns
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2015-02-14
 * @modified    2015-02-19
 *********************************************************************/
#ifndef SPACESHOOTER_LEVEL_H_
    #define SPACESHOOTER_LEVEL_H_

#include <queue>
#include <string>

#ifdef _WIN32
	#include <SDL.h>
#endif

#ifdef linux
	#include <SDL2/SDL.h>
#endif

#include "IObserver.h"
#include "Timer.h"

class GameEntity;

struct SpawnData;

class Level : public IObservable
{
    private:
        int currentLevel;
        bool doneLevel;
        int levelFinishTime;

        std::string levelXmlPaths[1];
        int levelXmlPathsSize;

        Timer timer;
        int nextSpawnTime;
        std::queue<int> timerQueue;
        std::queue<SpawnData> dataQueue;
        std::queue<SpawnData> spawningQueue;

        void parse();

    public:
        //Constructor
        Level();

        //Destructor
        ~Level();

        //Level methods
        void parse(int level);
        void onUpdate();
        std::queue<SpawnData> getSpawningQueue();
        SpawnData popSpawningQueue();
        void pauseTimers();
        void resumeTimers();

        //Virtual methods from IObservable
        //void notify(GameEntity* entity, int event);
};

struct SpawnData
{
    std::string type;
    int x;
    int y;
    int health = 1;
};

#endif
