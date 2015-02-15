/*******************************************************************//*
 * Implementation of the GameEntityData class.
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2015-02-12
 * @modified    2015-02-14
 *********************************************************************/
#include "GameEntityData.h"

#include <string>
#include <SDL2/SDL.h>
#include "ApplicationState.h"
#include "GameEntity.h"

GameEntityData::GameEntityData()
: populated(false)
{
}

// Fills all of the EntityXmlStructs with data from the xml files
void GameEntityData::populate(ApplicationState* state)
{
    if (!populated)
    {
        backgroundData = xmlParser.parse(state, PARSE_BACKGROUND);
        effectData = xmlParser.parse(state, PARSE_EFFECT);
        physicalData = xmlParser.parse(state, PARSE_PHYSICAL);
        uiData = xmlParser.parse(state, PARSE_UI);
    }
}

// Returns an array of data for background entities
std::vector<EntityXmlStruct> GameEntityData::getBackgroundData(ApplicationState* state)
{
    populate(state);
    return backgroundData;
}

// Returns an array of data for effect entities
std::vector<EntityXmlStruct> GameEntityData::getEffectData(ApplicationState* state)
{
    populate(state);
    return effectData;
}

// Returns an array of data for physical entities
std::vector<EntityXmlStruct> GameEntityData::getPhysicalData(ApplicationState* state)
{
    populate(state);
    return physicalData;
}

// Returns an array of data for UI entities
std::vector<EntityXmlStruct> GameEntityData::getUIData(ApplicationState* state)
{
    populate(state);
    return uiData;
}

EntityXmlStruct GameEntityData::getDataByName(ApplicationState* state, std::string name)
{
    populate(state);
    std::vector<EntityXmlStruct>::iterator collectionIterator;
    for (   collectionIterator=physicalData.begin();
            collectionIterator!=physicalData.end();
            collectionIterator++)
    {
        if ((*collectionIterator).name == name)
        {
            return (*collectionIterator);
        }
    }
    for (   collectionIterator=effectData.begin();
            collectionIterator!=effectData.end();
            collectionIterator++)
    {
        if ((*collectionIterator).name == name)
        {
            return (*collectionIterator);
        }
    }

    fprintf(stderr, "[ERROR] getDataByName(): no data named %s\n", name.c_str());
    EntityXmlStruct error;
    return error;
}

