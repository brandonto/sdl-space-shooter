/*******************************************************************//*
 * Implementation of the GameEntity class.
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2014-08-10
 * @modified    2014-09-12
 *********************************************************************/
#include "GameEntity.h"

#include <cstddef>
#include <SDL2/SDL.h>
#include "InputComponent.h"
#include "RenderComponent.h"
#include "PhysicsComponent.h"

//Constructor
GameEntity::GameEntity()
:   position(0, 0),
    input(NULL),
    render(NULL),
    physics(NULL)
{}

GameEntity::~GameEntity()
{
    if (input!=NULL) { delete input; }
    if (render!=NULL) { delete render; }
    if (physics!=NULL) { delete physics; }
}

void GameEntity::addInputComponent(InputComponent* input)
{
    this->input = input;
}

void GameEntity::addRenderComponent(RenderComponent* render)
{
    this->render = render;
}

void GameEntity::addPhysicsComponent(PhysicsComponent* physics)
{
    this->physics = physics;
}

void GameEntity::onEvent(SDL_Event *event)
{
    if (input!=NULL) { input->update(event); }
}

void GameEntity::onUpdate()
{
    if (physics!=NULL) { physics->update(); }
}

void GameEntity::onRender()
{
    if (render!=NULL) { render->update(); }
}

InputComponent* GameEntity::getInputComponent()
{
    return input;
}

RenderComponent* GameEntity::getRenderComponent()
{
    return render;
}

PhysicsComponent* GameEntity::getPhysicsComponent()
{
    return physics;
}
