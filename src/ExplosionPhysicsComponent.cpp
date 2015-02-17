/*******************************************************************//*
 * Implementation of the ExplosionPhysicsComponent class.
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2014-09-25
 * @modified    2015-02-17
 *********************************************************************/
#include "ExplosionPhysicsComponent.h"

#include "AudioSystem.h"
#include "ExplosionRenderComponent.h"
#include "GameEntity.h"
#include "RenderComponent.h"
#include "WindowElements.h"

ExplosionPhysicsComponent::ExplosionPhysicsComponent(GameEntity* gameEntity,
                                            WindowElements* windowElements)
:   render(NULL), velocity(0, -1500)
{
    this->gameEntity = gameEntity;
    this->windowElements = windowElements;
    //render = dynamic_cast<ExplosionRenderComponent*>(gameEntity->getRenderComponent());
    render = gameEntity->getRenderComponent();
    durationTimer.start();
    AudioSystem::getInstance()->playSound("explosion");
}

ExplosionPhysicsComponent::~ExplosionPhysicsComponent()
{

}

void ExplosionPhysicsComponent::update()
{
	if (durationTimer.getTimeOnTimer()>100)
    {
        durationTimer.stop();
        if (!render->getTexture()->advanceAnimation())
        {
            gameEntity->remove = true;
        }
        else
        {
            durationTimer.start();
        }
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

