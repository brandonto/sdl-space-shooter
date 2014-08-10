/*******************************************************************//*
 * Interface containing one method that all components must implement
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2014-08-10
 * @modified    2014-08-10
 *********************************************************************/

class Component
{
    public:
        //Destructor
        ~Component(){};

        //Methods
        void update() = 0;
}

/*******************************************************************//*
 * Flags for type of component
 *********************************************************************/

enum ComponentFlags
{
    //Application states
    COMPONENT_INPUT     = 0x01,
    COMPONENT_GRAPHICS  = 0x02,
    COMPONENT_RENDER    = 0x03,
    //COMPONENT_INPUT     = 0x04,
    //COMPONENT_INPUT     = 0x05,
    //COMPONENT_INPUT     = 0x06,
    //COMPONENT_INPUT     = 0x07,
    //COMPONENT_INPUT     = 0x08,
    //COMPONENT_INPUT     = 0x09,
};

