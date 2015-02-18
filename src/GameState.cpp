/*******************************************************************//*
 * Implementation of the GameState class.
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2014-09-05
 * @modified    2015-02-17
 *********************************************************************/
#include "GameState.h"

#include <SDL2/SDL.h>
#include "ApplicationStateManager.h"
#include "AudioSystem.h"
#include "GameEntity.h"
#include "Level.h"
#include "PauseState.h" //For the enumeration
#include "PlayerPhysicsComponent.h"
#include "WindowElements.h"

GameState::GameState(ApplicationStateManager* applicationStateManager,
                     WindowElements* windowElements)
:   blackScreen(windowElements),
    gameEntityManager(windowElements,this),
    nextState(0),
    pauseStatus(PAUSED_NONE),
    lives(3),
    playerDestroyed(true)
{
    this->applicationStateManager = applicationStateManager;
    this->windowElements = windowElements;
    this->xmlPath = "../data/xml/states/GameState.xml";
}

GameState::~GameState()
{
}

void GameState::onEnter()
{
    AudioSystem::getInstance()->loadMusic("level1");
    AudioSystem::getInstance()->playMusic();
    blackScreen.startBlackIn();
    background = gameEntityManager.getFactory()->createBackground();
    //std::vector<GameEntity*> enemyWave = gameEntityManager.getFactory()->createEnemyWaveStraight2();
    //enemies.insert(enemies.end(), enemyWave.begin(), enemyWave.end());
    //enemyWave = gameEntityManager.getFactory()->createEnemyWaveStraight3();
    //enemies.insert(enemies.end(), enemyWave.begin(), enemyWave.end());
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

    if (playerDestroyed)
    {
        if (lives>0)
        {
            player = gameEntityManager.getFactory()->createEntity("player");
        }
        else
        {
            //state transition
        }
        playerDestroyed = false;
    }

    level.onUpdate();
    while (!level.getSpawningQueue().empty())
    {
        SpawnData data = level.popSpawningQueue();
        gameEntityManager.getFactory()->createEntity(data);
    }

    gameEntityManager.onUpdate();
    if (pauseStatus == PAUSED_THIS_FRAME)
    {
        gameEntityManager.pauseAllTimers();
        level.pauseTimers();
        AudioSystem::getInstance()->pauseMusic();
        setPauseStatus(PAUSED_NONE);
    }
    else if (pauseStatus == UNPAUSED_THIS_FRAME)
    {
        gameEntityManager.resumeAllTimers();
        level.resumeTimers();
        AudioSystem::getInstance()->playMusic();
        setPauseStatus(PAUSED_NONE);
    }
}

void GameState::onRender()
{
    gameEntityManager.onRender();
}

void GameState::onExit()
{
    AudioSystem::getInstance()->stopMusic();
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

void GameState::onNotify(GameEntity* entity, int event)
{
    switch (event)
    {
        case PLAYER_DESTROYED:
            lives--;
            playerDestroyed = true;
            break;
    }
}
