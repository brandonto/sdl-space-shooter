/*******************************************************************//*
 * Implementation of the GameState class.
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2014-09-05
 * @modified    2014-09-17
 *********************************************************************/
#include "GameState.h"

#include <SDL2/SDL.h>
#include "ApplicationStateManager.h"
#include "GameEntity.h"
#include "PauseState.h" //For the enumeration
#include "WindowElements.h"

GameState::GameState(ApplicationStateManager* applicationStateManager,
                     WindowElements* windowElements)
:   blackScreen(windowElements), gameEntityManager(windowElements),
    nextState(0), pauseStatus(PAUSED_NONE)
{
    this->applicationStateManager = applicationStateManager;
    this->windowElements = windowElements;
}

GameState::~GameState()
{

}

void GameState::onEnter()
{
    blackScreen.startBlackIn();
    background = gameEntityManager.createBackground();
    player = gameEntityManager.createPlayer();
    meteor = gameEntityManager.createMeteor();
    std::vector<GameEntity*> enemyWave = gameEntityManager.createEnemyWaveStraight2();
    enemies.insert(enemies.end(), enemyWave.begin(), enemyWave.end());
    enemyWave = gameEntityManager.createEnemyWaveStraight3();
    enemies.insert(enemies.end(), enemyWave.begin(), enemyWave.end());
}

void GameState::onEvent()
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
                    applicationStateManager->pushStateOnStack(STATE_GAMEMENU);
                    setPauseStatus(PAUSED_THIS_FRAME);
                    break;

                case SDL_SCANCODE_P:
                    applicationStateManager->pushStateOnStack(STATE_PAUSE);
                    setPauseStatus(PAUSED_THIS_FRAME);
                    break;
            }
        }
        gameEntityManager.onEvent(&event);
    }
}

void GameState::onUpdate()
{
    if (blackScreen.isBlackingIn())
    {
        blackScreen.onUpdate();
        if (!blackScreen.isBlackingIn())
        {
            //Do something when black in is done
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
    if (pauseStatus == PAUSED_THIS_FRAME)
    {
        gameEntityManager.pauseAllTimers();
        setPauseStatus(PAUSED_NONE);
    }
    else if (pauseStatus == UNPAUSED_THIS_FRAME)
    {
        gameEntityManager.resumeAllTimers();
        setPauseStatus(PAUSED_NONE);
    }
}

void GameState::onRender()
{
    gameEntityManager.onRender();
}

void GameState::onExit()
{

}

void GameState::stateTransition(int nextState)
{
    blackScreen.startBlackOut();
    this->nextState = nextState;
}

void GameState::setPauseStatus(int pauseStatus)
{
    this->pauseStatus = pauseStatus;
}
