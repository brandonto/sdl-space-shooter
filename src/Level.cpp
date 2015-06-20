/*******************************************************************//*
 * Implementation of the Level class.
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2015-02-14
 * @modified    2015-02-25
 *********************************************************************/
#include "Level.h"

#include <cstdio>

#include "GameState.h" // Observing
#include "tinyxml.h"
#include "Util.h"

Level::Level()
:   currentLevel(0),
    doneLevel(true),
    nextSpawnTime()
{
    levelXmlPaths[0] = Util::fix_path("../data/xml/levels/level1.xml");
    levelXmlPaths[1] = Util::fix_path("../data/xml/levels/boss.xml");
    //levelXmlPaths[0] = Util::fix_path("../data/xml/levels/boss.xml");
}

Level::~Level()
{
}

// This function will parse through an XML file to construct an array of
// EntityXmlStruct structures
void Level::parse(int level)
{
    TiXmlDocument xmlDoc;

    // Return false if the XML file is not found
    if (!xmlDoc.LoadFile(levelXmlPaths[level].c_str()))
    {
        printf("[ERROR] parse(): Xml file not found.\n");
        return;
    }

    // The root element of this xml file
    TiXmlElement* rootElement = xmlDoc.RootElement();

    // Parsing the settings element
    TiXmlElement* settings = rootElement->FirstChildElement();
    if (settings == NULL)
    {
        printf("[ERROR] parse(): settings element not found.\n");
        return;
    }
    levelFinishTime = atoi(settings->Attribute("time"));
    levelMusic = settings->Attribute("music");
    if (settings->Attribute("boss-level") != NULL)
    {
        bossLevel = true;
    }
    else
    {
        bossLevel = false;
    }

    // The parsing EnemyType root element of this xml file
    TiXmlElement* rootEnemyType = settings->NextSiblingElement();
    std::string value = "EnemyType";
    if (rootEnemyType->Value() != value)
    {
        printf("[ERROR] parse(): EnemyType root element not found.\n");
        return;
    }

    // Parses through subelements of the EnemyType element and
    // fills data queue and time queue as we go
    for (   TiXmlElement* e = rootEnemyType->FirstChildElement();
            e != NULL;
            e = e->NextSiblingElement())
    {
        timerQueue.push(atoi(e->Attribute("spawn-time")));

        SpawnData data;
        data.x = atoi(e->Attribute("x"));
        data.y = atoi(e->Attribute("y"));
        // Converting c_str to std::string
        const char* cString = e->Attribute("type");
        int cStringSize = strlen(cString);
        data.type.assign(cString, cStringSize);
        if (e->Attribute("health") != NULL)
        {
            data.health = atoi(e->Attribute("health"));
        }

        dataQueue.push(data);
    }

    nextSpawnTime = timerQueue.front();
}

void Level::onUpdate()
{
    if (doneLevel)
    {
        if (currentLevel < LEVEL_XML_PATH_SIZE)
        {
            timer.stop();
            doneLevel = false;
            parse(currentLevel++);
            notify(NULL, LEVEL_COMPLETED);
            timer.start();
        }
        else
        {
            notify(NULL, GAME_COMPLETED);
            return;
        }
    }

    while (timer.getTimeOnTimer() > nextSpawnTime)
    {
        if (!timerQueue.empty() && !dataQueue.empty())
        {
            nextSpawnTime = timerQueue.front();
            timerQueue.pop();
            SpawnData toSpawn = dataQueue.front();
            dataQueue.pop();
            spawningQueue.push(toSpawn);
        }
        else
        {
            // Level is done... waiting for level transition
            nextSpawnTime = levelFinishTime+1000;
        }
    }

    if (!bossLevel && timer.getTimeOnTimer() > levelFinishTime)
    {
        doneLevel = true;
    }
}

std::string Level::getMusic()
{
    return levelMusic;
}

std::queue<SpawnData> Level::getSpawningQueue()
{
    return spawningQueue;
}

SpawnData Level::popSpawningQueue()
{
    SpawnData data = spawningQueue.front();
    spawningQueue.pop();
    return data;
}

void Level::pauseTimers()
{
    timer.pause();
}

void Level::resumeTimers()
{
    timer.resume();
}
