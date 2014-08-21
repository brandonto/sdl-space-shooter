/*******************************************************************//*
 * Implementation of the GameEntityManager class.
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2014-08-10
 * @modified    2014-08-20
 *********************************************************************/
#include "GameEntityManager.h"

#include <SDL2/SDL.h>
#include "BackgroundRenderComponent.h"
#include "GameEntity.h"

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

void GameEntityManager::createBackground(SDL_Renderer* renderer)
{
    backgroundLayer.add(new GameEntity(new BackgroundRenderComponent(renderer)));
}


