/*******************************************************************//*
 * Implementation of the GameEntityManager class.
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2014-08-10
 * @modified    2015-02-19
 *********************************************************************/
#include "GameEntityManager.h"

#include <string>

#ifdef _WIN32
	#include <SDL.h>
#endif

#ifdef __linux
	#include <SDL2/SDL.h>
#endif

#include "ApplicationState.h"
#include "GameEntity.h"
#include "WindowElements.h"

GameEntityManager::GameEntityManager(WindowElements* windowElements,
                                    ApplicationState* gameState)
:   windowElements(windowElements),
    gameState(gameState),
    collisionManager(windowElements),
    gameEntityFactory(this,windowElements)
{
}

// Event handling
void GameEntityManager::onEvent(SDL_Event* event)
{
    physicalLayer.onEvent(event);
    uiLayer.onEvent(event);
}

// Update game logic
void GameEntityManager::onUpdate()
{
    backgroundLayer.onUpdate();
    physicalLayer.onUpdate();
    effectLayer.onUpdate();
}

// Renders frame
void GameEntityManager::onRender()
{
    backgroundLayer.onRender();
    physicalLayer.onRender();
    effectLayer.onRender();
    uiLayer.onRender();
}

// Pauses game timers
void GameEntityManager::pauseAllTimers()
{
    physicalLayer.onPauseTimers();
    effectLayer.onPauseTimers();
}

// Resumes game timers
void GameEntityManager::resumeAllTimers()
{
    physicalLayer.onResumeTimers();
    effectLayer.onResumeTimers();
}

// Adds an entity to the background layer
void GameEntityManager::addBackgroundEntity(GameEntity* gameEntity)
{
    backgroundLayer.add(gameEntity);
}

// Adds an entity to the physical layer
void GameEntityManager::addPhysicalEntity(GameEntity* gameEntity)
{
    physicalLayer.add(gameEntity);
}

// Adds an entity to the effect layer
void GameEntityManager::addEffectEntity(GameEntity* gameEntity)
{
    effectLayer.add(gameEntity);
}

// Adds an entity to the user interface layer
void GameEntityManager::addUIEntity(GameEntity* gameEntity)
{
    uiLayer.add(gameEntity);
}

// Getter for ApplicationState
ApplicationState* GameEntityManager::getState()
{
    return gameState;
}

// Getter for CollisionManager
CollisionManager* GameEntityManager::getCollisionManager()
{
    return &collisionManager;
}


// Getter for GameEntityFactory
GameEntityFactory* GameEntityManager::getFactory()
{
    return &gameEntityFactory;
}

