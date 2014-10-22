/*******************************************************************//*
 * The core component bag class for the component-entity system used in
 * throughout this game. Doesn't do anything useful apart from holding
 * references to the various components
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2014-08-10
 * @modified    2014-10-21
 *********************************************************************/
#ifndef SPACESHOOTER_GAMEENTITY_H_
    #define SPACESHOOTER_GAMEENTITY_H_

#include "Vector2D.h"

class InputComponent;
class RenderComponent;
class PhysicsComponent;
class CollisionComponent;

union SDL_Event;

class GameEntity
{
    private:
        //Fields
        InputComponent* input;
        RenderComponent* render;
        PhysicsComponent* physics;
        CollisionComponent* collision;

    public:
        //Fields
        Vector2D position;
        bool remove;
        bool active;

        //Constructor
        GameEntity();

        //Destructor
        ~GameEntity();

        //Methods
        void addInputComponent(InputComponent* input);
        void addRenderComponent(RenderComponent* render);
        void addPhysicsComponent(PhysicsComponent* physics);
        void addCollisionComponent(CollisionComponent* collision);
        void onEvent(SDL_Event* event);
        void onUpdate();
        void onRender();
        virtual void onDestroy();

        RenderComponent* getRenderComponent();
        InputComponent* getInputComponent();
        PhysicsComponent* getPhysicsComponent();
        CollisionComponent* getCollisionComponent();
};

#endif
