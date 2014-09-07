/*******************************************************************//*
 * Render component for background
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2014-08-17
 * @modified    2014-09-06
 *********************************************************************/
#ifndef SPACESHOOTER_BACKGROUNDRENDERCOMPONENT_
    #define SPACESHOOTER_BACKGROUNDRENDERCOMPONENT_

#include "RenderComponent.h"

struct SDL_Texture;
struct WindowElements;

class BackgroundRenderComponent : public RenderComponent
{
    private:
        SDL_Texture* sprite;
        WindowElements* windowElements;
        int offset;
        int offsetIncrementCounter;
        int offsetIncrementModulus;

    public:
        //Constructor
        BackgroundRenderComponent(WindowElements* windowElements);

        //Destructor
        ~BackgroundRenderComponent();

        //Methods
        void update();
};

#endif
