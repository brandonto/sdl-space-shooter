/*******************************************************************//*
 * Implementation of the GameEntityManager class.
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2014-08-10
 * @modified    2014-09-01
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

std::vector<GameEntity*> GameEntityManager::createMainMenu(WindowElements* windowElements)
{
    GameEntity* mainMenu[1];

    GameEntity* uiTitle = new GameEntity();
    uiTitle->addRenderComponent(new UITitleRenderComponent(uiTitle, windowElements));
    uiLayer.add(uiTitle);
    mainMenu[0] = uiTitle;

    std::vector<GameEntity*> mainMenuVector(mainMenu, mainMenu + sizeof(mainMenu)/sizeof(GameEntity*));

    return mainMenuVector;
}

GameEntity* GameEntityManager::createBackground(WindowElements* windowElements)
{
    GameEntity* background = new GameEntity();
    background->addRenderComponent(new BackgroundRenderComponent(windowElements));
    backgroundLayer.add(background);

    return background;
}

