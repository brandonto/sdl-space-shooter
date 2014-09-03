/*******************************************************************//*
 * Implementation of the GameEntityManager class.
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2014-08-10
 * @modified    2014-09-03
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
    GameEntity* mainMenu[6];

    int xGrid = windowElements->WINDOW_WIDTH/15;
    int yGrid = windowElements->WINDOW_HEIGHT/24;

    GameEntity* uiTitle = new GameEntity();
    UIPanelRenderComponent* uiTitleRender = new UIPanelRenderComponent(uiTitle, windowElements);
    temp.x = 3*xGrid;
    temp.y = 3*yGrid;
    temp.w = 9*xGrid;
    temp.h = 6*yGrid;
    uiTitleRender->setRenderRect(&temp);
    temp.x = 12;
    temp.y = 0;
    temp.w = 80;
    temp.h = 60;
    //printf("x = %d", temp.x);
    //printf("y = %d", temp.y);
    uiTitleRender->addText("Space", 96, &temp, true);
    temp.x = 5;
    temp.y = 45;
    temp.w = 94;
    temp.h = 70;
    uiTitleRender->addText("Shooter", 96, &temp, true);
    uiTitleRender->enableBlending();
    uiTitle->addRenderComponent(uiTitleRender);
    uiLayer.add(uiTitle);
    mainMenu[0] = uiTitle;

    GameEntity* uiPlay = new GameEntity();
    UIPanelRenderComponent* uiPlayRender = new UIPanelRenderComponent(uiPlay, windowElements);
    temp.x = 5*xGrid;
    temp.y = 11*yGrid;
    temp.w = 5*xGrid;
    temp.h = 1*yGrid;
    uiPlayRender->setRenderRect(&temp);
    temp.x = 12;
    temp.y = 5;
    temp.w = 80;
    temp.h = 100;
    uiPlayRender->addText("Play", 96, &temp, true);
    uiPlayRender->enableBlending();
    uiPlay->addRenderComponent(uiPlayRender);
    uiLayer.add(uiPlay);
    mainMenu[1] = uiPlay;

    GameEntity* uiInstructions = new GameEntity();
    UIPanelRenderComponent* uiInstructionsRender = new UIPanelRenderComponent(uiInstructions, windowElements);
    temp.x = 5*xGrid;
    temp.y = 13*yGrid;
    temp.w = 5*xGrid;
    temp.h = 1*yGrid;
    uiInstructionsRender->setRenderRect(&temp);
    temp.x = 12;
    temp.y = 5;
    temp.w = 80;
    temp.h = 100;
    uiInstructionsRender->addText("Instructions", 96, &temp, true);
    uiInstructionsRender->enableBlending();
    uiInstructions->addRenderComponent(uiInstructionsRender);
    uiLayer.add(uiInstructions);
    mainMenu[2] = uiInstructions;

    GameEntity* uiOptions = new GameEntity();
    UIPanelRenderComponent* uiOptionsRender = new UIPanelRenderComponent(uiOptions, windowElements);
    temp.x = 5*xGrid;
    temp.y = 15*yGrid;
    temp.w = 5*xGrid;
    temp.h = 1*yGrid;
    uiOptionsRender->setRenderRect(&temp);
    temp.x = 12;
    temp.y = 5;
    temp.w = 80;
    temp.h = 100;
    uiOptionsRender->addText("Options", 96, &temp, true);
    uiOptionsRender->enableBlending();
    uiOptions->addRenderComponent(uiOptionsRender);
    uiLayer.add(uiOptions);
    mainMenu[3] = uiOptions;

    GameEntity* uiCredits = new GameEntity();
    UIPanelRenderComponent* uiCreditsRender = new UIPanelRenderComponent(uiCredits, windowElements);
    temp.x = 5*xGrid;
    temp.y = 17*yGrid;
    temp.w = 5*xGrid;
    temp.h = 1*yGrid;
    uiCreditsRender->setRenderRect(&temp);
    temp.x = 12;
    temp.y = 5;
    temp.w = 80;
    temp.h = 100;
    uiCreditsRender->addText("Credits", 96, &temp, true);
    uiCreditsRender->enableBlending();
    uiCredits->addRenderComponent(uiCreditsRender);
    uiLayer.add(uiCredits);
    mainMenu[4] = uiCredits;

    GameEntity* uiQuit = new GameEntity();
    UIPanelRenderComponent* uiQuitRender = new UIPanelRenderComponent(uiQuit, windowElements);
    temp.x = 5*xGrid;
    temp.y = 19*yGrid;
    temp.w = 5*xGrid;
    temp.h = 1*yGrid;
    uiQuitRender->setRenderRect(&temp);
    temp.x = 12;
    temp.y = 5;
    temp.w = 80;
    temp.h = 100;
    uiQuitRender->addText("Quit", 96, &temp, true);
    uiQuitRender->enableBlending();
    uiQuit->addRenderComponent(uiQuitRender);
    uiLayer.add(uiQuit);
    mainMenu[5] = uiQuit;

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

