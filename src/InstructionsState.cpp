/*******************************************************************//*
 * Implementation of the InstructionsState class.
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2015-01-31
 * @modified    2015-02-01
 *********************************************************************/
#include "InstructionsState.h"

#include <SDL2/SDL.h>
#include "ApplicationStateManager.h"
#include "GameEntity.h"
#include "RenderComponent.h"
#include "WindowElements.h"

InstructionsState::InstructionsState(ApplicationStateManager* applicationStateManager,
                     WindowElements* windowElements)
:   fadeIn(false), fadeOut(false), uiAlpha(0), nextState(0),
    gameEntityManager(windowElements), blackScreen(windowElements)
{
    this->applicationStateManager = applicationStateManager;
    this->windowElements = windowElements;
}

InstructionsState::~InstructionsState()
{
}

void InstructionsState::onEnter()
{
    blackScreen.startBlackIn();
    background = gameEntityManager.createBackground();
    uiInstructions = gameEntityManager.createUIInstructions(this);
    playerInstructions = gameEntityManager.createPlayerInstructions();

    // Initializes alpha value of ui to 0
    for (int i=0; i<uiInstructions.size(); i++)
    {
        uiInstructions[i]->getRenderComponent()->setAlphaBlend(uiAlpha);
    }
    playerInstructions->getRenderComponent()->setAlphaBlend(uiAlpha);
}

void InstructionsState::onEvent()
{
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
        {
            applicationStateManager->setNextState(STATE_EXIT);
        }
        else if (event.type == SDL_KEYDOWN)
        {
            switch(event.key.keysym.scancode)
            {
                case SDL_SCANCODE_ESCAPE:
                    stateTransition(STATE_MENU);
                    break;
            }
        }
        gameEntityManager.onEvent(&event);
    }
}

void InstructionsState::onUpdate()
{
    if (fadeIn)
    {
        if (uiAlpha<200)
        {
            uiAlpha+=10;
            if (uiAlpha==200) { fadeIn = false; }
        }
        for (int i=0; i<uiInstructions.size(); i++)
        {
            uiInstructions[i]->getRenderComponent()->setAlphaBlend(uiAlpha);
        }
        playerInstructions->getRenderComponent()->setAlphaBlend(uiAlpha);
    }
    else if (fadeOut)
    {
        if (uiAlpha>0)
        {
            uiAlpha-=10;
            if (uiAlpha==0) { fadeOut = false; blackScreen.startBlackOut(); }
        }
        for (int i=0; i<uiInstructions.size(); i++)
        {
            uiInstructions[i]->getRenderComponent()->setAlphaBlend(uiAlpha);
        }
        playerInstructions->getRenderComponent()->setAlphaBlend(uiAlpha);
    }
    else if (blackScreen.isBlackingIn())
    {
        blackScreen.onUpdate();
        if (!blackScreen.isBlackingIn())
        {
            fadeIn = true;
        }
    }
    else if (blackScreen.isBlackingOut())
    {
        blackScreen.onUpdate();
        if (!blackScreen.isBlackingOut())
        {
            applicationStateManager->setNextState(nextState);
        }
    }

    gameEntityManager.onUpdate();
}

void InstructionsState::onRender()
{
    //SDL_RenderClear(windowElements->renderer);
    gameEntityManager.onRender();
    //SDL_RenderPresent(windowElements->renderer);
}

void InstructionsState::onExit()
{

}

void InstructionsState::stateTransition(int nextState)
{
    this->nextState = nextState;
    fadeOut = true;
}
