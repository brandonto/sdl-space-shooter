/*******************************************************************//*
 * Input component for UI panel
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2014-09-03
 * @modified    2014-09-03
 *********************************************************************/
#ifndef SPACESHOOTER_UIPANELINPUTCOMPONENT_
    #define SPACESHOOTER_UIPANELINPUTCOMPONENT_

#include "InputComponent.h"
#include <SDL2/SDL.h>

class GameEntity;
class UIPanelRenderComponent;

class UIPanelInputComponent : public InputComponent
{
    private:
        GameEntity* gameEntity;
        UIPanelRenderComponent* render;
        SDL_Rect* uiRect;

    public:
        //Constructor
        UIPanelInputComponent(GameEntity* gameEntity);

        //Destructor
        ~UIPanelInputComponent();

        //Methods
        void update(SDL_Event* event);
};

#endif
