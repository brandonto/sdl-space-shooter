/*******************************************************************//*
 * Implementation of the GameEntityManager class.
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2014-08-10
 * @modified    2014-09-19
 *********************************************************************/
#include "GameEntityManager.h"

#include <string>
#include <SDL2/SDL.h>
#include "ApplicationState.h"
#include "BackgroundPhysicsComponent.h"
#include "BackgroundRenderComponent.h"
#include "EnemyPhysicsComponent.h"
#include "EnemyRenderComponent.h"
#include "EnemyProjectilePhysicsComponent.h"
#include "EnemyProjectileRenderComponent.h"
#include "GameEntity.h"
#include "MeteorPhysicsComponent.h"
#include "MeteorRenderComponent.h"
#include "PlayerCollisionComponent.h"
#include "PlayerInputComponent.h"
#include "PlayerPhysicsComponent.h"
#include "PlayerRenderComponent.h"
#include "PlayerProjectilePhysicsComponent.h"
#include "PlayerProjectileRenderComponent.h"
#include "UIClickFunctionQuit.h"
#include "UIClickFunctionPlay.h"
#include "UIPanelInputComponent.h"
#include "UIPanelRenderComponent.h"
#include "WindowElements.h"

GameEntityManager::GameEntityManager(WindowElements* windowElements)
:   windowElements(windowElements), collisionManager(windowElements)
{

}

void GameEntityManager::onEvent(SDL_Event* event)
{
    physicalLayer.onEvent(event);
    uiLayer.onEvent(event);
}

void GameEntityManager::onUpdate()
{
    backgroundLayer.onUpdate();
    physicalLayer.onUpdate();
    effectLayer.onUpdate();
}

void GameEntityManager::onRender()
{
    backgroundLayer.onRender();
    physicalLayer.onRender();
    effectLayer.onUpdate();
    uiLayer.onRender();
}

void GameEntityManager::pauseAllTimers()
{
    physicalLayer.onPauseTimers();
    effectLayer.onPauseTimers();
}

void GameEntityManager::resumeAllTimers()
{
    physicalLayer.onResumeTimers();
    effectLayer.onPauseTimers();
}

std::vector<GameEntity*> GameEntityManager::createMainMenu(ApplicationState* state)
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
    temp.x = 11;
    temp.y = 0;
    temp.w = 80;
    temp.h = 60;
    //printf("x = %d", temp.x);
    //printf("y = %d", temp.y);
    uiTitleRender->addText("Space", 96, &temp, true);
    temp.x = 5;
    temp.y = 45;
    temp.w = 92;
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
    temp.x = 11;
    temp.y = 5;
    temp.w = 80;
    temp.h = 100;
    uiPlayRender->addText("Play", 96, &temp, true);
    uiPlayRender->enableBlending();
    uiPlay->addRenderComponent(uiPlayRender);
    UIPanelInputComponent* uiPlayInput = new UIPanelInputComponent(uiPlay);
    uiPlayInput->addClickFunction(new UIClickFunctionPlay(state));
    uiPlay->addInputComponent(uiPlayInput);
    uiLayer.add(uiPlay);
    mainMenu[1] = uiPlay;

    GameEntity* uiInstructions = new GameEntity();
    UIPanelRenderComponent* uiInstructionsRender = new UIPanelRenderComponent(uiInstructions, windowElements);
    temp.x = 5*xGrid;
    temp.y = 13*yGrid;
    temp.w = 5*xGrid;
    temp.h = 1*yGrid;
    uiInstructionsRender->setRenderRect(&temp);
    temp.x = 11;
    temp.y = 5;
    temp.w = 80;
    temp.h = 100;
    uiInstructionsRender->addText("Instructions", 96, &temp, true);
    uiInstructionsRender->enableBlending();
    uiInstructions->addRenderComponent(uiInstructionsRender);
    UIPanelInputComponent* uiInstructionsInput = new UIPanelInputComponent(uiInstructions);
    uiInstructions->addInputComponent(uiInstructionsInput);
    uiLayer.add(uiInstructions);
    mainMenu[2] = uiInstructions;

    GameEntity* uiOptions = new GameEntity();
    UIPanelRenderComponent* uiOptionsRender = new UIPanelRenderComponent(uiOptions, windowElements);
    temp.x = 5*xGrid;
    temp.y = 15*yGrid;
    temp.w = 5*xGrid;
    temp.h = 1*yGrid;
    uiOptionsRender->setRenderRect(&temp);
    temp.x = 11;
    temp.y = 5;
    temp.w = 80;
    temp.h = 100;
    uiOptionsRender->addText("Options", 96, &temp, true);
    uiOptionsRender->enableBlending();
    uiOptions->addRenderComponent(uiOptionsRender);
    UIPanelInputComponent* uiOptionsInput = new UIPanelInputComponent(uiOptions);
    uiOptions->addInputComponent(uiOptionsInput);
    uiLayer.add(uiOptions);
    mainMenu[3] = uiOptions;

    GameEntity* uiCredits = new GameEntity();
    UIPanelRenderComponent* uiCreditsRender = new UIPanelRenderComponent(uiCredits, windowElements);
    temp.x = 5*xGrid;
    temp.y = 17*yGrid;
    temp.w = 5*xGrid;
    temp.h = 1*yGrid;
    uiCreditsRender->setRenderRect(&temp);
    temp.x = 11;
    temp.y = 5;
    temp.w = 80;
    temp.h = 100;
    uiCreditsRender->addText("Credits", 96, &temp, true);
    uiCreditsRender->enableBlending();
    uiCredits->addRenderComponent(uiCreditsRender);
    UIPanelInputComponent* uiCreditsInput = new UIPanelInputComponent(uiCredits);
    uiCredits->addInputComponent(uiCreditsInput);
    uiLayer.add(uiCredits);
    mainMenu[4] = uiCredits;

    GameEntity* uiQuit = new GameEntity();
    UIPanelRenderComponent* uiQuitRender = new UIPanelRenderComponent(uiQuit, windowElements);
    temp.x = 5*xGrid;
    temp.y = 19*yGrid;
    temp.w = 5*xGrid;
    temp.h = 1*yGrid;
    uiQuitRender->setRenderRect(&temp);
    temp.x = 11;
    temp.y = 5;
    temp.w = 80;
    temp.h = 100;
    uiQuitRender->addText("Quit", 96, &temp, true);
    uiQuitRender->enableBlending();
    uiQuit->addRenderComponent(uiQuitRender);
    UIPanelInputComponent* uiQuitInput = new UIPanelInputComponent(uiQuit);
    uiQuitInput->addClickFunction(new UIClickFunctionQuit(state));
    uiQuit->addInputComponent(uiQuitInput);
    uiLayer.add(uiQuit);
    mainMenu[5] = uiQuit;

    std::vector<GameEntity*> mainMenuVector(mainMenu, mainMenu + sizeof(mainMenu)/sizeof(GameEntity*));

    return mainMenuVector;
}

GameEntity* GameEntityManager::createBackground()
{
    GameEntity* background = new GameEntity();
    background->addRenderComponent(new BackgroundRenderComponent(background, windowElements));
    background->addPhysicsComponent(new BackgroundPhysicsComponent(background, windowElements));
    backgroundLayer.add(background);

    return background;
}

GameEntity* GameEntityManager::createEnemy()
{
    GameEntity* enemy = new GameEntity();
    enemy->addRenderComponent(new EnemyRenderComponent(enemy, windowElements));
    enemy->addPhysicsComponent(new EnemyPhysicsComponent(enemy, windowElements, this));
    physicalLayer.add(enemy);

    return enemy;
}

GameEntity* GameEntityManager::createEnemyProjectile(GameEntity* enemyEntity)
{
    GameEntity* projectile = new GameEntity();
    projectile->addRenderComponent(new EnemyProjectileRenderComponent(projectile, windowElements, enemyEntity));
    projectile->addPhysicsComponent(new EnemyProjectilePhysicsComponent(projectile, windowElements));
    physicalLayer.add(projectile);

    return projectile;
}

std::vector<GameEntity*> GameEntityManager::createEnemyWaveStraight2()
{
    GameEntity* enemyWave[2];

    enemyWave[0] = createEnemy();
    enemyWave[0]->position.x = windowElements->WINDOW_WIDTH/3;

    enemyWave[1] = createEnemy();
    enemyWave[1]->position.x = windowElements->WINDOW_WIDTH*2/3;

    std::vector<GameEntity*> enemyWaveVector(enemyWave, enemyWave + sizeof(enemyWave)/sizeof(GameEntity*));

    return enemyWaveVector;
}

std::vector<GameEntity*> GameEntityManager::createEnemyWaveStraight3()
{
    GameEntity* enemyWave[3];

    enemyWave[0] = createEnemy();
    enemyWave[0]->position.x = windowElements->WINDOW_WIDTH*1/6;

    enemyWave[1] = createEnemy();
    enemyWave[1]->position.x = windowElements->WINDOW_WIDTH*3/6;

    enemyWave[2] = createEnemy();
    enemyWave[2]->position.x = windowElements->WINDOW_WIDTH*5/6;

    std::vector<GameEntity*> enemyWaveVector(enemyWave, enemyWave + sizeof(enemyWave)/sizeof(GameEntity*));

    return enemyWaveVector;
}

GameEntity* GameEntityManager::createPlayer()
{
    GameEntity* player = new GameEntity();
    player->addRenderComponent(new PlayerRenderComponent(player, windowElements));
    player->addPhysicsComponent(new PlayerPhysicsComponent(player, windowElements, this));
    player->addCollisionComponent(new PlayerCollisionComponent(player, windowElements, &collisionManager));
    player->addInputComponent(new PlayerInputComponent(player, windowElements));
    physicalLayer.add(player);

    return player;
}

GameEntity* GameEntityManager::createPlayerProjectile(GameEntity* playerEntity)
{
    GameEntity* projectile = new GameEntity();
    projectile->addRenderComponent(new PlayerProjectileRenderComponent(projectile, windowElements, playerEntity));
    projectile->addPhysicsComponent(new PlayerProjectilePhysicsComponent(projectile, windowElements));
    physicalLayer.add(projectile);

    return projectile;
}

GameEntity* GameEntityManager::createMeteor()
{
    GameEntity* meteor = new GameEntity();
    meteor->addRenderComponent(new MeteorRenderComponent(meteor, windowElements));
    meteor->addPhysicsComponent(new MeteorPhysicsComponent(meteor, windowElements));
    physicalLayer.add(meteor);

    return meteor;
}
