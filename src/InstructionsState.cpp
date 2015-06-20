/*******************************************************************//*
 * Implementation of the InstructionsState class.
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2015-01-31
 * @modified    2015-02-20
 *********************************************************************/
#include "InstructionsState.h"

#ifdef _WIN32
	#include <SDL.h>
#endif

#ifdef __linux
	#include <SDL2/SDL.h>
#endif

#include "ApplicationStateManager.h"
#include "GameEntity.h"
#include "RenderComponent.h"
#include "Util.h"
#include "WindowElements.h"

InstructionsState::InstructionsState(ApplicationStateManager* applicationStateManager,
                     WindowElements* windowElements)
:   fadeIn(true),
    fadeOut(false),
    uiAlpha(0),
    nextState(-1),
    gameEntityManager(windowElements,this)
{
    this->applicationStateManager = applicationStateManager;
    this->windowElements = windowElements;
    this->stateEnum = STATE_INSTRUCTIONS;
    this->xmlPath = Util::fix_path("../data/xml/states/InstructionsState.xml"); //Default xml path
}

InstructionsState::~InstructionsState()
{
}

void InstructionsState::onEnter()
{
    uiEntities = gameEntityManager.getFactory()->createUIEntities();
    physicalEntities = gameEntityManager.getFactory()->createPlayerInstructions();

    // Initializes alpha value of ui to 0
    for (int i=0; i<uiEntities.size(); i++)
    {
        uiEntities[i]->getRenderComponent()->getTexture()->setAlphaBlend(uiAlpha);
    }
    physicalEntities[0]->getRenderComponent()->getTexture()->setAlphaBlend(uiAlpha);
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
                    statePop();
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
        for (int i=0; i<uiEntities.size(); i++)
        {
            uiEntities[i]->getRenderComponent()->getTexture()->setAlphaBlend(uiAlpha);
        }
        physicalEntities[0]->getRenderComponent()->getTexture()->setAlphaBlend(uiAlpha);
    }
    else if (fadeOut)
    {
        if (uiAlpha>0)
        {
            uiAlpha-=10;
            if (uiAlpha==0)
            {
                fadeOut = false;
                // stateTransition() called
                if (nextState != -1)
                {
                    applicationStateManager->setNextState(nextState);
                }
                // statePop() called
                else
                {
                    applicationStateManager->popStateOnStack();
                }
            }
        }
        for (int i=0; i<uiEntities.size(); i++)
        {
            uiEntities[i]->getRenderComponent()->getTexture()->setAlphaBlend(uiAlpha);
        }
        physicalEntities[0]->getRenderComponent()->getTexture()->setAlphaBlend(uiAlpha);
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

void InstructionsState::statePop()
{
    fadeOut = true;
}

