/*******************************************************************//*
 * The core component bag class for the component-entity system used in
 * throughout this game. Doesn't do anything useful apart from holding
 * references to the various components
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2014-08-10
 * @modified    2015-02-16
 *********************************************************************/
#ifndef SPACESHOOTER_GAMEENTITY_H_
    #define SPACESHOOTER_GAMEENTITY_H_

#include "Vector2D.h"

#include <string>

#include "StateEntityParser.h" //For EntityXmlStruct structure

class CollisionComponent;
class InputComponent;
class PhysicsComponent;
class RenderComponent;

union SDL_Event;

class GameEntity
{
    private:
        //Fields
        CollisionComponent* collision;
        InputComponent* input;
        PhysicsComponent* physics;
        RenderComponent* render;

        std::string id;
        std::string name;
        std::string type;

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
        void addCollisionComponent(CollisionComponent* collision);
        void addInputComponent(InputComponent* input);
        void addPhysicsComponent(PhysicsComponent* physics);
        void addRenderComponent(RenderComponent* render);
        void onEvent(SDL_Event* event);
        void onUpdate();
        void onRender();
        virtual void onHit();
        virtual void onDestroy();

        CollisionComponent* getCollisionComponent();
        InputComponent* getInputComponent();
        PhysicsComponent* getPhysicsComponent();
        RenderComponent* getRenderComponent();

        void setID(std::string id);
        std::string getID();
        void setName(std::string name);
        std::string getName();
        void setType(std::string type);
        std::string getType();
};

#endif
