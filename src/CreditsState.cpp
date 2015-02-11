/*******************************************************************//*
 * Implementation of the CreditsState class.
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2015-02-01
 * @modified    2015-02-10
 *********************************************************************/
#include "CreditsState.h"

#include <SDL2/SDL.h>
#include "ApplicationStateManager.h"
#include "GameEntity.h"
#include "RenderComponent.h"
#include "WindowElements.h"

CreditsState::CreditsState(ApplicationStateManager* applicationStateManager,
                     WindowElements* windowElements)
:   fadeIn(false),
    fadeOut(false),
    uiAlpha(0),
    nextState(0),
    gameEntityManager(windowElements,this),
    blackScreen(windowElements)
{
    this->applicationStateManager = applicationStateManager;
    this->windowElements = windowElements;
    this->stateEnum = STATE_CREDITS;
    this->xmlPath = "data/xml/states/CreditsState.xml"; //Default xml path
}

CreditsState::~CreditsState()
{
}

void CreditsState::onEnter()
{
    blackScreen.startBlackIn();
    backgroundEntities = gameEntityManager.getFactory()->createBackgroundEntities();
    uiEntities = gameEntityManager.getFactory()->createUIEntities();

    // Initializes alpha value of ui to 0
    for (int i=0; i<uiEntities.size(); i++)
    {
        uiEntities[i]->getRenderComponent()->getTexture()->setAlphaBlend(uiAlpha);
    }
}

void CreditsState::onEvent()
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

void CreditsState::onUpdate()
{
    if (fadeIn)
    {
        if (uiAlpha<200)
        {
            uiAlpha+=10;
            if (uiAlpha==200) { fadeIn = false; }
        }
        for (int i=0; i<uiEntities.size(); i++)
        {
            uiEntities[i]->getRenderComponent()->getTexture()->setAlphaBlend(uiAlpha);
        }
    }
    else if (fadeOut)
    {
        if (uiAlpha>0)
        {
            uiAlpha-=10;
            if (uiAlpha==0) { fadeOut = false; blackScreen.startBlackOut(); }
        }
        for (int i=0; i<uiEntities.size(); i++)
        {
            uiEntities[i]->getRenderComponent()->getTexture()->setAlphaBlend(uiAlpha);
        }
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

void CreditsState::onRender()
{
    //SDL_RenderClear(windowElements->renderer);
    gameEntityManager.onRender();
    //SDL_RenderPresent(windowElements->renderer);
}

void CreditsState::onExit()
{

}

void CreditsState::stateTransition(int nextState)
{
    this->nextState = nextState;
    fadeOut = true;
}
