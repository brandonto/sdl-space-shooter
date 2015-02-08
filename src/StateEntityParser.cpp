/*******************************************************************//*
 * Implementation of the StateEntityParser class.
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2015-02-07
 * @modified    2015-02-08
 *********************************************************************/
#include "StateEntityParser.h"

#include "ApplicationState.h"
#include "tinyxml.h"

StateEntityParser::StateEntityParser()
{
}

StateEntityParser::~StateEntityParser()
{
}

std::vector<EntityXmlStruct> StateEntityParser::parse(ApplicationState* state,
                                                    int parsingLayer)
{
    std::vector<EntityXmlStruct> xmlStructVector;

    TiXmlDocument xmlDoc;

    // Return false if the XML file is not found
    if (!xmlDoc.LoadFile(state->getXmlPath().c_str()))
    {
        fprintf(stderr, "[ERROR] parse(): Xml file not found.\n");
        return xmlStructVector;
    }

    // The root element of this xml file
    TiXmlElement* rootElement = xmlDoc.RootElement();

    // The parsing layer root element of this xml file
    TiXmlElement* rootParsingLayer = NULL;

    // Parses through State subelements to find correct parsing layer
    // element, then assigning it to it's own root variable
    for (   TiXmlElement* e = rootElement->FirstChildElement();
            e != NULL;
            e = e->NextSiblingElement())
    {
        if (e->Value() == mapEnumeration(parsingLayer))
        {
            rootParsingLayer = e;
        }
    }

    // Return false if the parsing layer element is not found
    if (rootParsingLayer == NULL)
    {
        fprintf(stderr, "[ERROR] parse(): Parsing layer elemenet not found.\n");
        return xmlStructVector;
    }

    int arraySize = 0;
    for (   TiXmlElement* e = rootParsingLayer->FirstChildElement();
            e != NULL;
            e = e->NextSiblingElement())
    {
        arraySize++;
    }

    printf("arraySize = %d\n", arraySize);
    return xmlStructVector;
}

// Private method that takes an enumerated int and returns a string
// representation of it
std::string StateEntityParser::mapEnumeration(int parsingLayer)
{
    std::string mappedString = "";
    switch (parsingLayer)
    {
        case PARSE_BACKGROUND:
            mappedString = "Background";
            break;

        case PARSE_PHYSICAL:
            mappedString = "Physical";
            break;

        case PARSE_EFFECT:
            mappedString = "Effect";
            break;

        case PARSE_UI:
            mappedString = "Ui";
            break;
    }
    return mappedString;
}
