/*******************************************************************//*
 * Implementation of the BossPhysicsComponent class.
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2015-02-21
 * @modified    2015-02-26
 *********************************************************************/
#include "BossPhysicsComponent.h"

#include <time.h>

#include "GameEntity.h"
#include "GameEntityFactory.h"
#include "GameState.h" // Observing
#include "Level.h" // For SpawnData struct
#include "RenderComponent.h"
#include "WindowElements.h"

BossPhysicsComponent::BossPhysicsComponent(GameEntity* gameEntity,
                                            WindowElements* windowElements,
                                            GameEntityFactory* gameEntityFactory)
:   gameEntityFactory(gameEntityFactory),
    render(NULL),
    shooting(true)
{
    this->gameEntity = gameEntity;
    this->windowElements = windowElements;
    render = gameEntity->getRenderComponent();
    srand(time(NULL));
}

BossPhysicsComponent::~BossPhysicsComponent()
{
}

void BossPhysicsComponent::update()
{
	float timeSinceLastFrame = timeBasedMovementTimer.getTimeOnTimer() / 1000.f;

    gameEntity->position += movement.getCurrentVelocity()*timeSinceLastFrame;

    int spriteWidth = render->getTexture()->getSpriteWidth();
    int spriteHeight = render->getTexture()->getSpriteHeight();

    if (!gameEntity->active)
    {
        if (gameEntity->position.x + spriteWidth/2 > 0 &&
            gameEntity->position.y + spriteHeight/2 > 0 &&
            gameEntity->position.x - spriteWidth/2 < windowElements->WINDOW_WIDTH &&
            gameEntity->position.y - spriteHeight/2 < windowElements->WINDOW_HEIGHT)
        {
            gameEntity->active = true;
        }
    }
    else
    {
        if (gameEntity->position.x + spriteWidth/2 + offScreenBuffer < 0 ||
            gameEntity->position.y + spriteHeight/2 + offScreenBuffer < 0 ||
            gameEntity->position.x - spriteWidth/2 - offScreenBuffer > windowElements->WINDOW_WIDTH ||
            gameEntity->position.y - spriteHeight/2 - offScreenBuffer > windowElements->WINDOW_HEIGHT)
        {
            gameEntity->remove = true;
            notify(gameEntity, GAME_OVER);
        }

        if (!gameEntity->remove && shooting)
        {
            if (projectileCapTimer.isStarted())
            {
                if (projectileCapTimer.getTimeOnTimer()>2500)
                {
                    SpawnData data;
                    data.type = "enemyProjectile";
                    data.x = gameEntity->position.x - render->getRenderRect().w/4;
                    data.y = gameEntity->position.y + render->getRenderRect().h/2;
                    gameEntityFactory->createEntity(data);
                    data.x = gameEntity->position.x + render->getRenderRect().w/4;
                    gameEntityFactory->createEntity(data);
                    projectileCapTimer.stop();
                }
            }
            else
            {
                SpawnData data;
                data.type = "enemyProjectile";
                data.x = gameEntity->position.x - render->getRenderRect().w/4;
                data.y = gameEntity->position.y + render->getRenderRect().h/2;
                gameEntityFactory->createEntity(data);
                data.x = gameEntity->position.x + render->getRenderRect().w/4;
                gameEntityFactory->createEntity(data);
            }
            projectileCapTimer.start();
        }

        if (!gameEntity->remove && shooting)
        {
            sprayTimer.start();
            if (sprayTimer.getTimeOnTimer()>10000)
            {
                sprayCapTimer.start();
                if (sprayCapTimer.getTimeOnTimer()>150)
                {
                    SpawnData data;
                    data.type = "enemyProjectile";
                    data.x = gameEntity->position.x - render->getRenderRect().w/3
                            + rand()%(int)(2*render->getRenderRect().w/3);
                    data.y = gameEntity->position.y + render->getRenderRect().h/2;
                    gameEntityFactory->createEntity(data);
                    sprayCapTimer.stop();
                }
                if (sprayTimer.getTimeOnTimer()>12000)
                {
                    sprayTimer.stop();
                }
            }
        }

        if (!gameEntity->remove && shooting)
        {
            spawnUFOTimer.start();
            if (spawnUFOTimer.getTimeOnTimer()>20000)
            {
                SpawnData data;
                data.type = "enemyUFO";
                data.x = gameEntity->position.x - render->getRenderRect().w/2;
                data.y = gameEntity->position.y;
                gameEntityFactory->createEntity(data);
                data.x = gameEntity->position.x + render->getRenderRect().w/2;
                gameEntityFactory->createEntity(data);
                spawnUFOTimer.stop();
            }
        }

        if (!gameEntity->remove && shooting)
        {
            nukeTimer.start();
            if (nukeTimer.getTimeOnTimer()>50000)
            {
                SpawnData data;
                data.type = "enemyProjectile";
                data.x = gameEntityFactory->getPlayerPosition().x;
                data.y = gameEntityFactory->getPlayerPosition().y;
                data.width = 2*windowElements->WINDOW_WIDTH;
                data.height = 2*windowElements->WINDOW_HEIGHT;
                gameEntityFactory->createEntity(data);
                nukeTimer.stop();
            }
        }
    }
    timeBasedMovementTimer.stop();
    timeBasedMovementTimer.start();
}

void BossPhysicsComponent::pauseTimers()
{
    timeBasedMovementTimer.pause();
    projectileCapTimer.pause();
    sprayTimer.pause();
    sprayCapTimer.pause();
    spawnUFOTimer.pause();
    nukeTimer.pause();
    movement.pauseTimers();
}

void BossPhysicsComponent::resumeTimers()
{
    timeBasedMovementTimer.resume();
    projectileCapTimer.resume();
    sprayTimer.resume();
    sprayCapTimer.resume();
    spawnUFOTimer.resume();
    nukeTimer.resume();
    movement.resumeTimers();
}

void BossPhysicsComponent::onHit()
{
    if (!decrementHealth(1))
    {
        onDestroy();
    }
}

void BossPhysicsComponent::onDestroy()
{
    //gameEntityFactory->createExplosion(gameEntity);
    SpawnData data;
    data.type = "explosion";
    data.x = gameEntity->position.x;
    data.y = gameEntity->position.y;
    data.width = render->getRenderRect().w;
    data.height = render->getRenderRect().w; //This is intended!!
    gameEntityFactory->createEntity(data);
    gameEntity->remove = true;
    notify(gameEntity, ENEMY_DESTROYED);
    notify(gameEntity, GAME_COMPLETED);
}

MovementPattern* BossPhysicsComponent::getMovementPattern()
{
    return &movement;
}

