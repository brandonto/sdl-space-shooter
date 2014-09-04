/*******************************************************************//*
 * Render component for UI panel
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2014-08-28
 * @modified    2014-09-03
 *********************************************************************/
#ifndef SPACESHOOTER_UIPANELRENDERCOMPONENT_
    #define SPACESHOOTER_UIPANELRENDERCOMPONENT_

#include "RenderComponent.h"
#include <string>
#include <SDL2/SDL.h>

class GameEntity;

struct WindowElements;

class UIPanelRenderComponent : public RenderComponent
{
    private:
        SDL_Rect renderRect;
        SDL_Surface* spriteSurface;
        SDL_Texture* sprite;
        GameEntity* gameEntity;
        WindowElements* windowElements;
        Uint8 alpha;
        const Uint8 SELECTED_ALPHA = 255;
        Uint8 cachedAlpha;
        bool selected;

    public:
        //Constructor
        UIPanelRenderComponent(GameEntity* gameEntity,
                               WindowElements* windowElements);

        //Destructor
        ~UIPanelRenderComponent();

        //Methods
        void update(GameEntity* gameEntity);
        void enableBlending();
        void setAlphaBlend(Uint8 alpha);
        Uint8 getAlphaBlend();
        bool isSelected();
        void toggleSelected();
        void setRenderRect(SDL_Rect* rect);
        SDL_Rect* getRenderRect();
        void addText(std::string text, int fontSize, SDL_Rect* destRect, bool scaled);
        bool buttonReady();
};

#endif
