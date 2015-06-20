/*******************************************************************//*
 * Implementation of the GameOverState class.
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2015-02-19
 * @modified    2015-02-19
 *********************************************************************/
#include "GameOverState.h"

#ifdef _WIN32
	#include <SDL.h>
#endif

#ifdef __linux
	#include <SDL2/SDL.h>
#endif

#include "ApplicationStateManager.h"
#include "AudioSystem.h"
#include "GameEntity.h"
#include "GameState.h"
#include "PauseState.h"
#include "RenderComponent.h"
#include "SDL_util.h"
#include "Util.h"
#include "WindowElements.h"

GameOverState::GameOverState(ApplicationStateManager* applicationStateManager,
                     WindowElements* windowElements)
:   fadeIn(true),
    fadeOut(false),
    menuAlpha(0),
    nextState(0),
    transitioningStates(false),
    gameEntityManager(windowElements,this),
    blackScreen(windowElements)
{
    this->applicationStateManager = applicationStateManager;
    this->windowElements = windowElements;
    this->stateEnum = STATE_GAMEOVER;
    this->xmlPath = Util::fix_path("../data/xml/states/GameOverState.xml");
}

GameOverState::~GameOverState()
{

}

void GameOverState::onEnter()
{
    AudioSystem::getInstance()->loadMusic("gameOver");
    AudioSystem::getInstance()->playMusic();
    blackScreen.setAlphaBlend(0);
    uiEntities = gameEntityManager.getFactory()->createUIEntities();
}

void GameOverState::onEvent()
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

                case SDL_SCANCODE_RETURN:
                    stateTransition(STATE_GAME);
                    break;
            }
        }
        gameEntityManager.onEvent(&event);
    }
}

void GameOverState::onUpdate()
{
    if (fadeIn)
    {
        if (menuAlpha<200)
        {
            menuAlpha+=5;
            if (menuAlpha==200) { fadeIn = false; }
        }
        for (int i=0; i<uiEntities.size(); i++)
        {
            uiEntities[i]->getRenderComponent()->getTexture()->setAlphaBlend(menuAlpha);
        }
    }
    else if (fadeOut)
    {
        if (menuAlpha>0)
        {
            menuAlpha-=10;
            if (menuAlpha==0)
            {
                fadeOut = false;
                if (transitioningStates)
                {
                    blackScreen.startBlackOut();
                }
                else
                {
                    applicationStateManager->popStateOnStack();
                    dynamic_cast<GameState*>(applicationStateManager->getMainState())->setPauseStatus(UNPAUSED_THIS_FRAME);
                }
            }
        }
        for (int i=0; i<uiEntities.size(); i++)
        {
            uiEntities[i]->getRenderComponent()->getTexture()->setAlphaBlend(menuAlpha);
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

void GameOverState::onRender()
{
    gameEntityManager.onRender();
    blackScreen.onRender();
}

void GameOverState::onExit()
{
    fadeOut = true;
    AudioSystem::getInstance()->stopMusic();
}

void GameOverState::stateTransition(int nextState)
{
    this->nextState = nextState;
    fadeOut = true;
    transitioningStates = true;
    AudioSystem::getInstance()->stopMusic();
}

