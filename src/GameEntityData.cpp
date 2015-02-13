/*******************************************************************//*
 * Implementation of the GameEntityData class.
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2015-02-12
 * @modified    2015-02-12
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

