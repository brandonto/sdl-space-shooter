/*******************************************************************//*
 * Implementation of the GameEntityManager class.
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2014-08-10
 * @modified    2014-08-30
 *********************************************************************/
#include "GameEntityManager.h"

#include <SDL2/SDL.h>
#include "BackgroundRenderComponent.h"
#include "GameEntity.h"
#include "UITitleRenderComponent.h"
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
    uiLayer.onRender();
}

void GameEntityManager::createMainMenu(WindowElements* windowElements)
{
    GameEntity* uiTitle = new GameEntity();
    uiTitle->addRenderComponent(new UITitleRenderComponent(uiTitle, windowElements));
    uiLayer.add(uiTitle);
}

void GameEntityManager::createBackground(WindowElements* windowElements)
{
    GameEntity* background = new GameEntity();
    background->addRenderComponent(new BackgroundRenderComponent(windowElements));
    backgroundLayer.add(background);
}

