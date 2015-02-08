/*******************************************************************//*
 * Render component for UI panel.
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2014-08-28
 * @modified    2015-02-08
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
        Uint8 cachedAlpha;
        bool selected;

    public:
        //Constructor
        UIPanelRenderComponent(GameEntity* gameEntity,
                               WindowElements* windowElements);

        //Destructor
        ~UIPanelRenderComponent();

        //Methods
        void update();
        bool isSelected();
        void toggleSelected();
        bool buttonReady();
};

#endif
