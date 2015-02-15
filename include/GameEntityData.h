/*******************************************************************//*
 * This class stores the xml data of State Entities
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2015-02-12
 * @modified    2015-02-14
 *********************************************************************/
#ifndef SPACESHOOTER_GAMEENTITYDATA_H_
    #define SPACESHOOTER_GAMEENTITYDATA_H_

#include <vector>
#include "StateEntityParser.h"

class ApplicationState;
class GameEntity;

struct WindowElements;

class GameEntityData
{
    private:
        StateEntityParser xmlParser;

        std::vector<EntityXmlStruct> backgroundData;
        std::vector<EntityXmlStruct> effectData;
        std::vector<EntityXmlStruct> physicalData;
        std::vector<EntityXmlStruct> uiData;

        bool populated;

    public:
        GameEntityData();

        void populate(ApplicationState* state);

        std::vector<EntityXmlStruct> getBackgroundData(ApplicationState* state);
        std::vector<EntityXmlStruct> getEffectData(ApplicationState* state);
        std::vector<EntityXmlStruct> getPhysicalData(ApplicationState* state);
        std::vector<EntityXmlStruct> getUIData(ApplicationState* state);

        EntityXmlStruct getDataByID(std::string id);
        EntityXmlStruct getDataByName(ApplicationState* state, std::string name);
};

#endif

