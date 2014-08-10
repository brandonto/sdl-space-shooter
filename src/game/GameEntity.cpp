/*******************************************************************//*
 * Implementation of the GameEntity class.
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2014-08-10
 * @modified    2014-08-10
 *********************************************************************/
#include "GameEntity.h"

//Constructor
GameEntity::GameEntity( GraphicsComponent* graphics,
                        RenderComponent* render
                      )
:   xPos(0), yPos(0), velocity(0),
    //input(input),
    graphics(graphics),
    render(render)
{}

void GameEntity::onEvent()
{
    //if (input!=NULL) { input->update(); }
}

void GameEntity::onUpdate()
{
    //if (graphics!=NULL) { graphics->update(); }
}

void GameEntity::onRender()
{
    //if (render!=NULL) { render->update(); }
}
