/*******************************************************************//*
 * Implementation of the GameEntityManager class.
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2014-08-10
 * @modified    2014-09-01
 *********************************************************************/
#include "GameEntityManager.h"

#include <string>
#include <SDL2/SDL.h>
#include "BackgroundRenderComponent.h"
#include "GameEntity.h"
#include "UIPanelRenderComponent.h"
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
    SDL_Rect temp;
    GameEntity* mainMenu[1];

    GameEntity* uiTitle = new GameEntity();
    UIPanelRenderComponent* uiTitleRender = new UIPanelRenderComponent(uiTitle, windowElements);
    temp.x = windowElements->WINDOW_WIDTH/5;
    temp.y = windowElements->WINDOW_HEIGHT/12;
    temp.w = windowElements->WINDOW_WIDTH - 2*temp.x;
    temp.h = windowElements->WINDOW_HEIGHT - 9*temp.y;
    uiTitleRender->setRenderRect(&temp);
    uiTitleRender->addText("Space Shooter", 72, &temp);
    uiTitle->addRenderComponent(uiTitleRender);
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

