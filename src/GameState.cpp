/*******************************************************************//*
 * Implementation of the GameState class.
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2014-09-05
 * @modified    2015-02-26
 *********************************************************************/
#include "GameState.h"

#ifdef _WIN32
	#include <SDL.h>
#endif

#ifdef __linux
	#include <SDL2/SDL.h>
#endif

#include "ApplicationStateManager.h"
#include "AudioSystem.h"
#include "BossPhysicsComponent.h"
#include "EnemyPhysicsComponent.h"
#include "GameEntity.h"
#include "Level.h"
#include "PauseState.h" //For the enumeration
#include "PlayerPhysicsComponent.h"
#include "UILivesRenderComponent.h"
#include "UIScoreRenderComponent.h"
#include "Util.h"
#include "WindowElements.h"

GameState::GameState(ApplicationStateManager* applicationStateManager,
                     WindowElements* windowElements)
:   blackScreen(windowElements),
    gameEntityManager(windowElements,this),
    nextState(0),
    pauseStatus(PAUSED_NONE),
    lives(3),
    score(0),
    playerDestroyed(true)
{
    this->applicationStateManager = applicationStateManager;
    this->windowElements = windowElements;
    this->stateEnum = STATE_GAME;
    this->xmlPath = Util::fix_path("../data/xml/states/GameState.xml");
}

GameState::~GameState()
{
}

void GameState::onEnter()
{
    level.addObserver(this);
    blackScreen.startBlackIn();
    background = gameEntityManager.getFactory()->createBackground();
    uiLives = gameEntityManager.getFactory()->createEntity("uiLives");
    dynamic_cast<UILivesRenderComponent*>(uiLives->getRenderComponent())->setLivesPointer(&lives);
    uiScore = gameEntityManager.getFactory()->createEntity("uiScore");
    dynamic_cast<UIScoreRenderComponent*>(uiScore->getRenderComponent())->setScorePointer(&score);
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
            gameOverTimer.start();
        }
        playerDestroyed = false;
    }

    if (gameOverTimer.isStarted())
    {
        if (gameOverTimer.getTimeOnTimer()>3000)
        {
            applicationStateManager->pushStateOnStack(STATE_GAMEOVER);
            setPauseStatus(PAUSED_THIS_FRAME);
            AudioSystem::getInstance()->stopMusic();
            gameOverTimer.stop();
        }
    }

    if (victoryTimer.isStarted())
    {
        if (victoryTimer.getTimeOnTimer()>3000)
        {
            applicationStateManager->pushStateOnStack(STATE_VICTORY);
            setPauseStatus(PAUSED_THIS_FRAME);
            AudioSystem::getInstance()->stopMusic();
            victoryTimer.stop();
        }
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
        case ENEMY_DESTROYED:
            score+=entity->getScore();
            //printf("SCORE = %d\n", score);
            break;

        case GAME_COMPLETED:
            victoryTimer.start();
            break;

        case GAME_OVER:
            gameOverTimer.start();
            break;

        case LEVEL_COMPLETED:
            AudioSystem::getInstance()->stopMusic();
            AudioSystem::getInstance()->loadMusic(level.getMusic());
            AudioSystem::getInstance()->playMusic();
            break;

        case PLAYER_DESTROYED:
            lives--;
            playerDestroyed = true;
            //printf("LIVES = %d\n", lives);
            break;
    }
}

