/*******************************************************************//*
 * Implementation of the GameEntityManager class.
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2014-08-10
 * @modified    2015-02-01
 *********************************************************************/
#include "GameEntityManager.h"

#include <string>
#include <SDL2/SDL.h>
#include "ApplicationState.h"
#include "BackgroundPhysicsComponent.h"
#include "BackgroundRenderComponent.h"
#include "EnemyCollisionComponent.h"
#include "EnemyPhysicsComponent.h"
#include "EnemyRenderComponent.h"
#include "ExplosionPhysicsComponent.h"
#include "ExplosionRenderComponent.h"
#include "EnemyProjectileCollisionComponent.h"
#include "EnemyProjectilePhysicsComponent.h"
#include "EnemyProjectileRenderComponent.h"
#include "GameEntity.h"
#include "MeteorPhysicsComponent.h"
#include "MeteorRenderComponent.h"
#include "PlayerCollisionComponent.h"
#include "PlayerInputComponent.h"
#include "PlayerPhysicsComponent.h"
#include "PlayerRenderComponent.h"
#include "PlayerProjectileCollisionComponent.h"
#include "PlayerProjectilePhysicsComponent.h"
#include "PlayerProjectileRenderComponent.h"
#include "SpriteRenderComponent.h"
#include "TextRenderComponent.h"
#include "UIClickFunctionQuit.h"
#include "UIClickFunctionPlay.h"
#include "UIClickFunctionInstructions.h"
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
    effectLayer.onRender();
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

    int xGrid = windowElements->WINDOW_WIDTH/30;
    int yGrid = windowElements->WINDOW_HEIGHT/48;

    GameEntity* uiTitle = new GameEntity();
    UIPanelRenderComponent* uiTitleRender = new UIPanelRenderComponent(uiTitle, windowElements);
    temp.x = 6*xGrid;
    temp.y = 6*yGrid;
    temp.w = 18*xGrid;
    temp.h = 12*yGrid;
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
    temp.x = 10*xGrid;
    temp.y = 22*yGrid;
    temp.w = 10*xGrid;
    temp.h = 2*yGrid;
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
    temp.x = 10*xGrid;
    temp.y = 26*yGrid;
    temp.w = 10*xGrid;
    temp.h = 2*yGrid;
    uiInstructionsRender->setRenderRect(&temp);
    temp.x = 11;
    temp.y = 5;
    temp.w = 80;
    temp.h = 100;
    uiInstructionsRender->addText("Instructions", 96, &temp, true);
    uiInstructionsRender->enableBlending();
    uiInstructions->addRenderComponent(uiInstructionsRender);
    UIPanelInputComponent* uiInstructionsInput = new UIPanelInputComponent(uiInstructions);
    uiInstructionsInput->addClickFunction(new UIClickFunctionInstructions(state));
    uiInstructions->addInputComponent(uiInstructionsInput);
    uiLayer.add(uiInstructions);
    mainMenu[2] = uiInstructions;

    GameEntity* uiOptions = new GameEntity();
    UIPanelRenderComponent* uiOptionsRender = new UIPanelRenderComponent(uiOptions, windowElements);
    temp.x = 10*xGrid;
    temp.y = 30*yGrid;
    temp.w = 10*xGrid;
    temp.h = 2*yGrid;
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
    temp.x = 10*xGrid;
    temp.y = 34*yGrid;
    temp.w = 10*xGrid;
    temp.h = 2*yGrid;
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
    temp.x = 10*xGrid;
    temp.y = 38*yGrid;
    temp.w = 10*xGrid;
    temp.h = 2*yGrid;
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

std::vector<GameEntity*> GameEntityManager::createUIInstructions(ApplicationState* state)
{
    SDL_Rect temp;
    GameEntity* instructionsMenu[4];

    int xGrid = windowElements->WINDOW_WIDTH/60;
    int yGrid = windowElements->WINDOW_HEIGHT/48;

    GameEntity* movement = new GameEntity();
    TextRenderComponent* movementRender = new TextRenderComponent(movement, windowElements);
    temp.x = 1*xGrid;
    temp.y = 2*yGrid;
    temp.w = 13*xGrid;
    temp.h = 5*yGrid;
    movementRender->setRenderRect(&temp);
    movementRender->setText("Movement:", 96);
    movementRender->enableBlending();
    movement->addRenderComponent(movementRender);
    uiLayer.add(movement);
    instructionsMenu[0] = movement;

    GameEntity* shoot = new GameEntity();
    TextRenderComponent* shootRender = new TextRenderComponent(shoot, windowElements);
    temp.x = 1*xGrid;
    temp.y = 8*yGrid;
    temp.w = 9*xGrid;
    temp.h = 5*yGrid;
    shootRender->setRenderRect(&temp);
    shootRender->setText("Shoot:", 96);
    shootRender->enableBlending();
    shoot->addRenderComponent(shootRender);
    uiLayer.add(shoot);
    instructionsMenu[1] = shoot;

    GameEntity* pause = new GameEntity();
    TextRenderComponent* pauseRender = new TextRenderComponent(pause, windowElements);
    temp.x = 1*xGrid;
    temp.y = 14*yGrid;
    temp.w = 9*xGrid;
    temp.h = 5*yGrid;
    pauseRender->setRenderRect(&temp);
    pauseRender->setText("Pause:", 96);
    pauseRender->enableBlending();
    pause->addRenderComponent(pauseRender);
    uiLayer.add(pause);
    instructionsMenu[2] = pause;

    GameEntity* menu = new GameEntity();
    TextRenderComponent* menuRender = new TextRenderComponent(menu, windowElements);
    temp.x = 1*xGrid;
    temp.y = 20*yGrid;
    temp.w = 9*xGrid;
    temp.h = 5*yGrid;
    menuRender->setRenderRect(&temp);
    menuRender->setText("Menu:", 96);
    menuRender->enableBlending();
    menu->addRenderComponent(menuRender);
    uiLayer.add(menu);
    instructionsMenu[3] = menu;

    //GameEntity* movement = new GameEntity();
    //UIPanelRenderComponent* movementRender = new UIPanelRenderComponent(movement, windowElements);
    //temp.x = 1*xGrid;
    //temp.y = 2*yGrid;
    //temp.w = 58*xGrid;
    //temp.h = 12*yGrid;
    //movementRender->setRenderRect(&temp);
    //temp.x = 10;
    //temp.y = 5;
    //temp.w = 60;
    //temp.h = 30;
    //movementRender->addText("Movement:", 96, &temp, true);
    //movementRender->enableBlending();
    //movement->addRenderComponent(movementRender);
    //uiLayer.add(movement);
    //instructionsMenu[0] = movement;

    //GameEntity* shoot = new GameEntity();
    //UIPanelRenderComponent* shootRender = new UIPanelRenderComponent(shoot, windowElements);
    //temp.x = 1*xGrid;
    //temp.y = 16*yGrid;
    //temp.w = 28*xGrid;
    //temp.h = 12*yGrid;
    //shootRender->setRenderRect(&temp);
    //temp.x = 10;
    //temp.y = 5;
    //temp.w = 60;
    //temp.h = 30;
    //shootRender->addText("Shoot:", 96, &temp, true);
    //shootRender->enableBlending();
    //shoot->addRenderComponent(shootRender);
    //uiLayer.add(shoot);
    //instructionsMenu[1] = shoot;

    //GameEntity* pause = new GameEntity();
    //UIPanelRenderComponent* pauseRender = new UIPanelRenderComponent(pause, windowElements);
    //temp.x = 31*xGrid;
    //temp.y = 16*yGrid;
    //temp.w = 28*xGrid;
    //temp.h = 12*yGrid;
    //pauseRender->setRenderRect(&temp);
    //temp.x = 10;
    //temp.y = 5;
    //temp.w = 60;
    //temp.h = 30;
    //pauseRender->addText("Pause:", 96, &temp, true);
    //pauseRender->enableBlending();
    //pause->addRenderComponent(pauseRender);
    //uiLayer.add(pause);
    //instructionsMenu[2] = pause;

    //GameEntity* menu = new GameEntity();
    //UIPanelRenderComponent* menuRender = new UIPanelRenderComponent(menu, windowElements);
    //temp.x = 1*xGrid;
    //temp.y = 30*yGrid;
    //temp.w = 28*xGrid;
    //temp.h = 12*yGrid;
    //menuRender->setRenderRect(&temp);
    //temp.x = 10;
    //temp.y = 5;
    //temp.w = 60;
    //temp.h = 30;
    //menuRender->addText("Menu:", 96, &temp, true);
    //menuRender->enableBlending();
    //menu->addRenderComponent(menuRender);
    //uiLayer.add(menu);
    //instructionsMenu[3] = menu;

    std::vector<GameEntity*> instructionsMenuVector(instructionsMenu, instructionsMenu + sizeof(instructionsMenu)/sizeof(GameEntity*));

    return instructionsMenuVector;
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
    enemy->addCollisionComponent(new EnemyCollisionComponent(enemy, windowElements, &collisionManager));
    physicalLayer.add(enemy);

    return enemy;
}

GameEntity* GameEntityManager::createEnemyProjectile(GameEntity* enemyEntity)
{
    GameEntity* projectile = new GameEntity();
    projectile->addRenderComponent(new EnemyProjectileRenderComponent(projectile, windowElements, enemyEntity));
    projectile->addPhysicsComponent(new EnemyProjectilePhysicsComponent(projectile, windowElements));
    projectile->addCollisionComponent(new EnemyProjectileCollisionComponent(projectile, windowElements, &collisionManager));
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

GameEntity* GameEntityManager::createExplosion(GameEntity* destroyedEntity)
{
    GameEntity* explosion = new GameEntity();
    explosion->addRenderComponent(new ExplosionRenderComponent(explosion, windowElements, destroyedEntity));
    explosion->addPhysicsComponent(new ExplosionPhysicsComponent(explosion, windowElements));
    effectLayer.add(explosion);

    return explosion;
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
    projectile->addCollisionComponent(new PlayerProjectileCollisionComponent(projectile, windowElements, &collisionManager));
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
