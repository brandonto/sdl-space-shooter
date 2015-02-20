/*******************************************************************//*
 * Interface containing one method that all render components must
 * implement
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2014-08-17
 * @modified    2015-02-20
 *********************************************************************/
#ifndef SPACESHOOTER_RENDERCOMPONENT_
    #define SPACESHOOTER_RENDERCOMPONENT_

#ifdef _WIN32
	#include <SDL.h>
#endif

#ifdef linux
	#include <SDL2/SDL.h>
#endif

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
        virtual void setRenderStatus(bool status){ renderEnabled = status; };
        virtual Texture* getTexture(){ return texture; };
        virtual SDL_Rect getRenderRect(){ return renderRect; };
        virtual bool advanceAnimation(){};

    protected:
        //Fields
        Texture* texture;
        SDL_Rect renderRect;

        GameEntity* gameEntity;
        WindowElements* windowElements;

        bool renderEnabled = true;
};

#endif
