/*******************************************************************//*
 * This is the Level class for the game. This class keeps track of
 * level specific data like enemy spawns
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2015-02-14
 * @modified    2015-02-15
 *********************************************************************/
#ifndef SPACESHOOTER_LEVEL_H_
    #define SPACESHOOTER_LEVEL_H_

#include <SDL2/SDL.h>
#include <queue>
#include <string>
#include "Timer.h"

class GameEntity;

struct SpawnData;

class Level
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
};

struct SpawnData
{
    std::string type;
    int x;
    int y;
};

#endif
