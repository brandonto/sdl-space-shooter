/*******************************************************************//*
 * The core component bag class for the component-entity system used in
 * throughout this game. Doesn't do anything useful apart from holding
 * references to the various components
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2014-08-10
 * @modified    2014-09-13
 *********************************************************************/
#ifndef SPACESHOOTER_GAMEENTITY_H_
    #define SPACESHOOTER_GAMEENTITY_H_

#include "Vector2D.h"

class InputComponent;
class RenderComponent;
class PhysicsComponent;

union SDL_Event;

class GameEntity
{
    private:
        //Fields
        InputComponent* input;
        RenderComponent* render;
        PhysicsComponent* physics;

    public:
        //Fields
        Vector2D position;
        bool remove;

        //Constructor
        GameEntity();

        //Destructor
        ~GameEntity();

        //Methods
        void addInputComponent(InputComponent* input);
        void addRenderComponent(RenderComponent* render);
        void addPhysicsComponent(PhysicsComponent* physics);
        void onEvent(SDL_Event* event);
        void onUpdate();
        void onRender();

        RenderComponent* getRenderComponent();
        InputComponent* getInputComponent();
        PhysicsComponent* getPhysicsComponent();
};

#endif
