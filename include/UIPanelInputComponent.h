/*******************************************************************//*
 * Input component for UI panel.
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2014-09-03
 * @modified    2015-02-19
 *********************************************************************/
#ifndef SPACESHOOTER_UIPANELINPUTCOMPONENT_
    #define SPACESHOOTER_UIPANELINPUTCOMPONENT_

#include "InputComponent.h"

#ifdef _WIN32
	#include <SDL.h>
#endif

#ifdef __linux
	#include <SDL2/SDL.h>
#endif

class GameEntity;
class UIClickFunction;
class UIPanelRenderComponent;

class UIPanelInputComponent : public InputComponent
{
    private:
        UIClickFunction* clickFunction;
        UIPanelRenderComponent* render;
        SDL_Rect uiRect;
        bool buttonPressedDown;

    public:
        //Constructor
        UIPanelInputComponent(GameEntity* gameEntity);

        //Destructor
        ~UIPanelInputComponent();

        //Methods
        void update(SDL_Event* event);
        void addClickFunction(UIClickFunction* clickFunction);
};

#endif
