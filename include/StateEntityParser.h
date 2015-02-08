/*******************************************************************//*
 * This class is responsible for parsing through XML data of state
 * entities
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2015-02-07
 * @modified    2015-02-08
 *********************************************************************/
#ifndef SPACESHOOTER_STATEENTITYPARSER_H_
    #define SPACESHOOTER_STATEENTITYPARSER_H_

#include <string>
#include <vector>
#include <SDL2/SDL.h>>

class ApplicationState;

struct EntityXmlStruct;

class StateEntityParser
{
    private:
        std::string mapEnumeration(int parsingLayer);

    public:
        //Constructor
        StateEntityParser();

        //Destructor
        ~StateEntityParser();

        //Methods
        std::vector<EntityXmlStruct> parse(ApplicationState* state,
                                        int parsingLayer);
};

struct EntityXmlStruct
{
    std::string id = "";
    std::string name = "";
    std::string type = "";
    std::string data = "";
    std::string texture = "";
    std::string function = "";

    SDL_Rect renderRect;
    //int x = 0;
    //int y = 0;
    //int width = 0;
    //int height = 0;

    bool alphaEnabled = false;
};

enum ParsingLayer
{
    PARSE_BACKGROUND,
    PARSE_PHYSICAL,
    PARSE_EFFECT,
    PARSE_UI,
};

#endif
