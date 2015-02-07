/*******************************************************************//*
 * Render component for text.
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2015-01-31
 * @modified    2015-02-06
 *********************************************************************/
#ifndef SPACESHOOTER_TEXTRENDERCOMPONENT_
    #define SPACESHOOTER_TEXTRENDERCOMPONENT_

#include "RenderComponent.h"
#include <string>
#include <SDL2/SDL.h>

class GameEntity;

struct WindowElements;

class TextRenderComponent : public RenderComponent
{
    public:
        //Constructor
        TextRenderComponent(GameEntity* gameEntity,
                               WindowElements* windowElements);

        //Destructor
        ~TextRenderComponent();

        //Methods
        void update();
        void setRenderRect(SDL_Rect* rect);
        void setText(std::string text, int fontSize);
};

#endif
