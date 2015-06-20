/*******************************************************************//*
 * Implementation of the GameMenuState class.
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2015-02-02
 * @modified    2015-02-20
 *********************************************************************/
#include "GameMenuState.h"

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

GameMenuState::GameMenuState(ApplicationStateManager* applicationStateManager,
                     WindowElements* windowElements)
:   fadeIn(true),
    fadeOut(false),
    menuAlpha(0),
    nextState(-1),
    pushedState(-1),
    gameEntityManager(windowElements,this),
    blackScreen(windowElements)
{
    this->applicationStateManager = applicationStateManager;
    this->windowElements = windowElements;
    this->stateEnum = STATE_GAMEMENU;
    this->xmlPath = Util::fix_path("../data/xml/states/GameMenuState.xml");
}

GameMenuState::~GameMenuState()
{

}

void GameMenuState::onEnter()
{
    blackScreen.setAlphaBlend(0);
    uiEntities = gameEntityManager.getFactory()->createUIEntities();
    AudioSystem::getInstance()->setMusicPlayingState(false);
}

void GameMenuState::onEvent()
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

void GameMenuState::onUpdate()
{
    if (fadeIn)
    {
        if (menuAlpha<200)
        {
            menuAlpha+=10;
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
                // stateTransition() called
                if (nextState != -1)
                {
                    blackScreen.startBlackOut();
                }
                // statePush() called
                else if (pushedState != -1)
                {
                    applicationStateManager->pushStateOnStack(pushedState);
                    fadeIn = true;
                    pushedState = -1;
                }
                // statePop() called
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

void GameMenuState::onRender()
{
    gameEntityManager.onRender();
    blackScreen.onRender();
}

void GameMenuState::onExit()
{
    AudioSystem::getInstance()->setMusicPlayingState(true);
}

void GameMenuState::stateTransition(int nextState)
{
    this->nextState = nextState;
    fadeOut = true;
}

void GameMenuState::statePush(int pushedState)
{
    this->pushedState = pushedState;
    fadeOut = true;
}

void GameMenuState::statePop()
{
    fadeOut = true;
}

