/*******************************************************************//*
 * This astract class encapsulates a function called on UI click
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2014-09-04
 * @modified    2014-09-05
 *********************************************************************/
#ifndef SPACESHOOTER_UICLICKFUNCTION_
    #define SPACESHOOTER_UICLICKFUNCTION_

class UIClickFunction
{
    private:

    public:
        //Destructor
        virtual ~UIClickFunction(){};

        //Methods
        virtual void onClick() = 0;
};

#endif
