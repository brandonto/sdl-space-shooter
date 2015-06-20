/*******************************************************************//*
 * Implementation of the GameEntity class.
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2014-08-10
 * @modified    2015-02-19
 *********************************************************************/
#include "GameEntity.h"

#include <cstddef>

#ifdef _WIN32
	#include <SDL.h>
#endif

#ifdef __linux
	#include <SDL2/SDL.h>
#endif

#include "CollisionComponent.h"
#include "InputComponent.h"
#include "PhysicsComponent.h"
#include "RenderComponent.h"

//Constructor
GameEntity::GameEntity()
:   position(0, 0),
    remove(false),
    active(false),
    id(""),
    name(""),
    type(""),
    collision(NULL),
    input(NULL),
    physics(NULL),
    render(NULL)
{}

GameEntity::~GameEntity()
{
    if (input!=NULL) { delete input; }
    if (collision!=NULL) { delete collision; }
    if (physics!=NULL) { delete physics; }
    if (render!=NULL) { delete render; }
}

void GameEntity::addCollisionComponent(CollisionComponent* collision)
{
    this->collision = collision;
}

void GameEntity::addInputComponent(InputComponent* input)
{
    this->input = input;
}

void GameEntity::addPhysicsComponent(PhysicsComponent* physics)
{
    this->physics = physics;
}

void GameEntity::addRenderComponent(RenderComponent* render)
{
    this->render = render;
}

void GameEntity::onEvent(SDL_Event *event)
{
    if (input!=NULL) { input->update(event); }
}

void GameEntity::onUpdate()
{
    if (physics!=NULL) { physics->update(); }
    if (collision!=NULL) { collision->update(); }
}

void GameEntity::onRender()
{
    if (render!=NULL) { render->update(); }
}

void GameEntity::onHit()
{
    if (physics!=NULL) { physics->onHit(); }
}

void GameEntity::onDestroy()
{
    if (physics!=NULL) { physics->onDestroy(); }
}

CollisionComponent* GameEntity::getCollisionComponent()
{
    return collision;
}

InputComponent* GameEntity::getInputComponent()
{
    return input;
}

PhysicsComponent* GameEntity::getPhysicsComponent()
{
    return physics;
}

RenderComponent* GameEntity::getRenderComponent()
{
    return render;
}

void GameEntity::setID(std::string id)
{
    this->id.assign(id);
}

std::string GameEntity::getID()
{
    return id;
}

void GameEntity::setName(std::string name)
{
    this->name.assign(name);
}

std::string GameEntity::getName()
{
    return name;
}

void GameEntity::setType(std::string type)
{
    this->type.assign(type);
}

std::string GameEntity::getType()
{
    return type;
}

