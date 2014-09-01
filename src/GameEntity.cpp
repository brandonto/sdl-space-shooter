/*******************************************************************//*
 * Implementation of the GameEntity class.
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2014-08-10
 * @modified    2014-09-01
 *********************************************************************/
#include "GameEntity.h"

#include <cstddef>
#include "RenderComponent.h"

//Constructor
GameEntity::GameEntity()
:   xPos(0), yPos(0), velocity(0)
{}

GameEntity::~GameEntity()
{
    if (render!=NULL) { delete render; }
}

void GameEntity::addRenderComponent(RenderComponent* render)
{
    this->render = render;
}

void GameEntity::onEvent()
{
    //if (input!=NULL) { input->update(); }
}

void GameEntity::onUpdate()
{
}

void GameEntity::onRender()
{
    if (render!=NULL) { render->update(this); }
}

RenderComponent* GameEntity::getRenderComponent()
{
    return render;
}
