/*******************************************************************//*
 * Implementation of the ExplosionPhysicsComponent class.
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2014-09-25
 * @modified    2014-09-25
 *********************************************************************/
#include "ExplosionPhysicsComponent.h"

#include "GameEntity.h"
#include "RenderComponent.h"
#include "WindowElements.h"

ExplosionPhysicsComponent::ExplosionPhysicsComponent(GameEntity* gameEntity,
                                            WindowElements* windowElements)
:   render(NULL), velocity(0, -1500)
{
    this->gameEntity = gameEntity;
    this->windowElements = windowElements;
    render = gameEntity->getRenderComponent();
    durationTimer.start();
}

ExplosionPhysicsComponent::~ExplosionPhysicsComponent()
{

}

void ExplosionPhysicsComponent::update()
{
	if (durationTimer.getTimeOnTimer()>1000)
    {
        durationTimer.stop();
        gameEntity->remove = true;
    }
}

void ExplosionPhysicsComponent::pauseTimers()
{
    durationTimer.pause();
}

void ExplosionPhysicsComponent::resumeTimers()
{
    durationTimer.resume();
}

