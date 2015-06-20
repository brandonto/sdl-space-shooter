/*******************************************************************//*
 * Implementation of the OptionsState class.
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2015-02-20
 * @modified    2015-02-20
 *********************************************************************/
#include "OptionsState.h"

#ifdef _WIN32
	#include <SDL.h>
#endif

#ifdef __linux
	#include <SDL2/SDL.h>
#endif

#include "ApplicationStateManager.h"
#include "AudioSystem.h"
#include "GameEntity.h"
#include "RenderComponent.h"
#include "Util.h"
#include "WindowElements.h"

OptionsState::OptionsState(ApplicationStateManager* applicationStateManager,
                     WindowElements* windowElements)
:   fadeIn(true),
    fadeOut(false),
    uiAlpha(0),
    nextState(-1),
    gameEntityManager(windowElements,this)
{
    this->applicationStateManager = applicationStateManager;
    this->windowElements = windowElements;
    this->stateEnum = STATE_OPTIONS;
    this->xmlPath = Util::fix_path("../data/xml/states/OptionsState.xml"); //Default xml path
}

OptionsState::~OptionsState()
{
}

void OptionsState::onEnter()
{
    uiEntities = gameEntityManager.getFactory()->createUIEntities();
    bgmCheck = gameEntityManager.getFactory()->createEntityByName("bgmCheck");
    bgmCheck->getRenderComponent()->setRenderStatus(AudioSystem::getInstance()->getMusicStatus());
    sfxCheck = gameEntityManager.getFactory()->createEntityByName("sfxCheck");
    sfxCheck->getRenderComponent()->setRenderStatus(AudioSystem::getInstance()->getSoundStatus());
    fullScreenCheck = gameEntityManager.getFactory()->createEntityByName("fullScreenCheck");
    fullScreenCheck->getRenderComponent()->setRenderStatus(windowElements->fullScreen);

    // Initializes alpha value of ui to 0
    for (int i=0; i<uiEntities.size(); i++)
    {
        uiEntities[i]->getRenderComponent()->getTexture()->setAlphaBlend(uiAlpha);
    }
}

void OptionsState::onEvent()
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

void OptionsState::onUpdate()
{
    bgmCheck->getRenderComponent()->setRenderStatus(AudioSystem::getInstance()->getMusicStatus());
    sfxCheck->getRenderComponent()->setRenderStatus(AudioSystem::getInstance()->getSoundStatus());
    fullScreenCheck->getRenderComponent()->setRenderStatus(windowElements->fullScreen);

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
            bgmCheck->getRenderComponent()->getTexture()->setAlphaBlend(uiAlpha);
            sfxCheck->getRenderComponent()->getTexture()->setAlphaBlend(uiAlpha);
            fullScreenCheck->getRenderComponent()->getTexture()->setAlphaBlend(uiAlpha);
        }
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
            bgmCheck->getRenderComponent()->getTexture()->setAlphaBlend(uiAlpha);
            sfxCheck->getRenderComponent()->getTexture()->setAlphaBlend(uiAlpha);
            fullScreenCheck->getRenderComponent()->getTexture()->setAlphaBlend(uiAlpha);
        }
    }

    gameEntityManager.onUpdate();
}

void OptionsState::onRender()
{
    //SDL_RenderClear(windowElements->renderer);
    gameEntityManager.onRender();
    //SDL_RenderPresent(windowElements->renderer);
}

void OptionsState::onExit()
{

}

void OptionsState::stateTransition(int nextState)
{
    this->nextState = nextState;
    fadeOut = true;
}

void OptionsState::statePop()
{
    fadeOut = true;
}


