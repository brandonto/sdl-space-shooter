/*******************************************************************//*
 * Interface containing one method that all input components must
 * implement
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2014-09-03
 * @modified    2014-09-06
 *********************************************************************/
#ifndef SPACESHOOTER_INPUTCOMPONENT_
    #define SPACESHOOTER_INPUTCOMPONENT_

union SDL_Event;

class InputComponent
{
    public:
        //Destructor
        virtual ~InputComponent(){};

        //Methods
        virtual void update(SDL_Event* event) = 0;
};

#endif
