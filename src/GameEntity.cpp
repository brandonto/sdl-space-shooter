/*******************************************************************//*
 * Implementation of the GameEntity class.
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2014-08-10
 * @modified    2014-08-20
 *********************************************************************/
#include "GameEntity.h"

#include <cstddef>
#include "RenderComponent.h"

//Constructor
GameEntity::GameEntity( RenderComponent* render
                      )
:   xPos(0), yPos(0), velocity(0),
    //input(input),
    render(render)
{}

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
