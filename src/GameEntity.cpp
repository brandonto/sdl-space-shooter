/*******************************************************************//*
 * Implementation of the GameEntity class.
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2014-08-10
 * @modified    2014-09-03
 *********************************************************************/
#include "GameEntity.h"

#include <cstddef>
#include <SDL2/SDL.h>
#include "InputComponent.h"
#include "RenderComponent.h"

//Constructor
GameEntity::GameEntity()
:   xPos(0), yPos(0), velocity(0)
{}

GameEntity::~GameEntity()
{
    if (input!=NULL) { delete input; }
    if (render!=NULL) { delete render; }
}

void GameEntity::addInputComponent(InputComponent* input)
{
    this->input = input;
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
}

void GameEntity::onRender()
{
    if (render!=NULL) { render->update(this); }
}

InputComponent* GameEntity::getInputComponent()
{
    if (input!=NULL) { return input; }
}

RenderComponent* GameEntity::getRenderComponent()
{
    if (render!=NULL) { return render; }
}
