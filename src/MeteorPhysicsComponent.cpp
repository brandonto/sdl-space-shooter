/*******************************************************************//*
 * Implementation of the MeteorPhysicsComponent class.
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2014-09-14
 * @modified    2014-09-14
 *********************************************************************/
#include "MeteorPhysicsComponent.h"

#include "GameEntity.h"
#include "GameEntityManager.h"
#include "MeteorRenderComponent.h"
#include "WindowElements.h"

MeteorPhysicsComponent::MeteorPhysicsComponent(GameEntity* gameEntity,
                                            WindowElements* windowElements)
:   gameEntity(gameEntity), windowElements(windowElements),
    gameEntityManager(gameEntityManager), render(NULL),
    velocity(-12, 5), velocityPerSecond(13),
    angleIncrementCounter(0), angleIncrementModulus(1)
{
    render = dynamic_cast<MeteorRenderComponent*>(gameEntity->getRenderComponent());
}

MeteorPhysicsComponent::~MeteorPhysicsComponent()
{

}

void MeteorPhysicsComponent::update()
{
	float timeSinceLastFrame = timeBasedMovementTimer.getTimeOnTimer() / 1000.f;
    //position = position + speedPerSecond*secondsSinceLastFrame
    gameEntity->position += velocity*timeSinceLastFrame;

    timeBasedMovementTimer.stop();
    timeBasedMovementTimer.start();

    angleIncrementCounter++;
    if (angleIncrementCounter % angleIncrementModulus == 0)
    {
        render->angle+=0.10;
    }
    if (render->angle >= 360)
    {
        render->angle = 0;
    }
}


