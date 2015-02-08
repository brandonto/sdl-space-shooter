/*******************************************************************//*
 * Interface containing one method that all render components must
 * implement
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2014-08-17
 * @modified    2015-02-08
 *********************************************************************/
#ifndef SPACESHOOTER_RENDERCOMPONENT_
    #define SPACESHOOTER_RENDERCOMPONENT_

#include <SDL2/SDL.h>
#include "Texture.h"

class GameEntity;

struct WindowElements;

class RenderComponent
{
    public:
        //Destructor
        virtual ~RenderComponent(){};

        //Methods
        virtual void update() = 0;
        virtual void setRenderRect(SDL_Rect* rect){ renderRect = *rect; };
        virtual Texture* getTexture(){ return texture; };
        virtual SDL_Rect getRenderRect(){ return renderRect; };
        virtual bool advanceAnimation(){};

    protected:
        //Fields
        Texture* texture;
        SDL_Rect renderRect;

        GameEntity* gameEntity;
        WindowElements* windowElements;
};

#endif
