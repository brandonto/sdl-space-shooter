/*******************************************************************//*
 * Implementation of the GameEntityManager class.
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2014-08-10
 * @modified    2014-08-27
 *********************************************************************/
#include "GameEntityManager.h"

#include <SDL2/SDL.h>
#include "BackgroundRenderComponent.h"
#include "GameEntity.h"
#include "WindowElements.h"

GameEntityManager::GameEntityManager()
{

}

void GameEntityManager::onEvent(SDL_Event event)
{

}

void GameEntityManager::onRender()
{
    backgroundLayer.onRender();
}

void GameEntityManager::createBackground(WindowElements* windowElements)
{
    backgroundLayer.add(new GameEntity(new BackgroundRenderComponent(windowElements)));
}


