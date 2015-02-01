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
#include "UIClickFunctionBack.h"
#include "UIClickFunctionCredits.h"
#include "UIClickFunctionFork.h"
#include "UIClickFunctionInstructions.h"
#include "UIClickFunctionPlay.h"
#include "UIClickFunctionQuit.h"
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
    temp.y = 21*yGrid;
    temp.w = 10*xGrid;
    temp.h = 3*yGrid;
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
    temp.h = 3*yGrid;
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
    temp.y = 31*yGrid;
    temp.w = 10*xGrid;
    temp.h = 3*yGrid;
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
    temp.y = 36*yGrid;
    temp.w = 10*xGrid;
    temp.h = 3*yGrid;
    uiCreditsRender->setRenderRect(&temp);
    temp.x = 11;
    temp.y = 5;
    temp.w = 80;
    temp.h = 100;
    uiCreditsRender->addText("Credits", 96, &temp, true);
    uiCreditsRender->enableBlending();
    uiCredits->addRenderComponent(uiCreditsRender);
    UIPanelInputComponent* uiCreditsInput = new UIPanelInputComponent(uiCredits);
    uiCreditsInput->addClickFunction(new UIClickFunctionCredits(state));
    uiCredits->addInputComponent(uiCreditsInput);
    uiLayer.add(uiCredits);
    mainMenu[4] = uiCredits;

    GameEntity* uiQuit = new GameEntity();
    UIPanelRenderComponent* uiQuitRender = new UIPanelRenderComponent(uiQuit, windowElements);
    temp.x = 10*xGrid;
    temp.y = 41*yGrid;
    temp.w = 10*xGrid;
    temp.h = 3*yGrid;
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
    GameEntity* instructionsMenu[18];

    int xGrid = windowElements->WINDOW_WIDTH/60;
    int yGrid = windowElements->WINDOW_HEIGHT/48;

    GameEntity* movementText = new GameEntity();
    TextRenderComponent* movementTextRender = new TextRenderComponent(movementText, windowElements);
    temp.x = 1*xGrid;
    temp.y = 2*yGrid;
    temp.w = 13*xGrid;
    temp.h = 5*yGrid;
    movementTextRender->setRenderRect(&temp);
    movementTextRender->setText("Movement:", 96);
    movementTextRender->enableBlending();
    movementText->addRenderComponent(movementTextRender);
    uiLayer.add(movementText);
    instructionsMenu[0] = movementText;

    GameEntity* keyW = new GameEntity();
    SpriteRenderComponent* keyWRender = new SpriteRenderComponent(keyW, windowElements);
    temp.x = 21*xGrid;
    temp.y = 2*yGrid;
    temp.w = 5*xGrid;
    temp.h = 5*yGrid;
    keyWRender->setRenderRect(&temp);
    keyWRender->setImage("bin/graphics/ui/Keyboard_White_W.png");
    keyWRender->enableBlending();
    keyW->addRenderComponent(keyWRender);
    uiLayer.add(keyW);
    instructionsMenu[1] = keyW;

    GameEntity* keyA = new GameEntity();
    SpriteRenderComponent* keyARender = new SpriteRenderComponent(keyA, windowElements);
    temp.x = 17*xGrid;
    temp.y = 6*yGrid;
    temp.w = 5*xGrid;
    temp.h = 5*yGrid;
    keyARender->setRenderRect(&temp);
    keyARender->setImage("bin/graphics/ui/Keyboard_White_A.png");
    keyARender->enableBlending();
    keyA->addRenderComponent(keyARender);
    uiLayer.add(keyA);
    instructionsMenu[2] = keyA;

    GameEntity* keyS = new GameEntity();
    SpriteRenderComponent* keySRender = new SpriteRenderComponent(keyS, windowElements);
    temp.x = 21*xGrid;
    temp.y = 6*yGrid;
    temp.w = 5*xGrid;
    temp.h = 5*yGrid;
    keySRender->setRenderRect(&temp);
    keySRender->setImage("bin/graphics/ui/Keyboard_White_S.png");
    keySRender->enableBlending();
    keyS->addRenderComponent(keySRender);
    uiLayer.add(keyS);
    instructionsMenu[3] = keyS;

    GameEntity* keyD = new GameEntity();
    SpriteRenderComponent* keyDRender = new SpriteRenderComponent(keyD, windowElements);
    temp.x = 25*xGrid;
    temp.y = 6*yGrid;
    temp.w = 5*xGrid;
    temp.h = 5*yGrid;
    keyDRender->setRenderRect(&temp);
    keyDRender->setImage("bin/graphics/ui/Keyboard_White_D.png");
    keyDRender->enableBlending();
    keyD->addRenderComponent(keyDRender);
    uiLayer.add(keyD);
    instructionsMenu[4] = keyD;

    GameEntity* orText = new GameEntity();
    TextRenderComponent* orTextRender = new TextRenderComponent(orText, windowElements);
    temp.x = 35*xGrid;
    temp.y = 4*yGrid;
    temp.w = 2*xGrid;
    temp.h = 5*yGrid;
    orTextRender->setRenderRect(&temp);
    orTextRender->setText("or", 96);
    orTextRender->enableBlending();
    orText->addRenderComponent(orTextRender);
    uiLayer.add(orText);
    instructionsMenu[5] = orText;

    GameEntity* keyUp = new GameEntity();
    SpriteRenderComponent* keyUpRender = new SpriteRenderComponent(keyUp, windowElements);
    temp.x = 46*xGrid;
    temp.y = 2*yGrid;
    temp.w = 5*xGrid;
    temp.h = 5*yGrid;
    keyUpRender->setRenderRect(&temp);
    keyUpRender->setImage("bin/graphics/ui/Keyboard_White_Arrow_Up.png");
    keyUpRender->enableBlending();
    keyUp->addRenderComponent(keyUpRender);
    uiLayer.add(keyUp);
    instructionsMenu[6] = keyUp;

    GameEntity* keyLeft = new GameEntity();
    SpriteRenderComponent* keyLeftRender = new SpriteRenderComponent(keyLeft, windowElements);
    temp.x = 42*xGrid;
    temp.y = 6*yGrid;
    temp.w = 5*xGrid;
    temp.h = 5*yGrid;
    keyLeftRender->setRenderRect(&temp);
    keyLeftRender->setImage("bin/graphics/ui/Keyboard_White_Arrow_Left.png");
    keyLeftRender->enableBlending();
    keyLeft->addRenderComponent(keyLeftRender);
    uiLayer.add(keyLeft);
    instructionsMenu[7] = keyLeft;

    GameEntity* keyDown = new GameEntity();
    SpriteRenderComponent* keyDownRender = new SpriteRenderComponent(keyDown, windowElements);
    temp.x = 46*xGrid;
    temp.y = 6*yGrid;
    temp.w = 5*xGrid;
    temp.h = 5*yGrid;
    keyDownRender->setRenderRect(&temp);
    keyDownRender->setImage("bin/graphics/ui/Keyboard_White_Arrow_Down.png");
    keyDownRender->enableBlending();
    keyDown->addRenderComponent(keyDownRender);
    uiLayer.add(keyDown);
    instructionsMenu[8] = keyDown;

    GameEntity* KeyRight = new GameEntity();
    SpriteRenderComponent* KeyRightRender = new SpriteRenderComponent(KeyRight, windowElements);
    temp.x = 50*xGrid;
    temp.y = 6*yGrid;
    temp.w = 5*xGrid;
    temp.h = 5*yGrid;
    KeyRightRender->setRenderRect(&temp);
    KeyRightRender->setImage("bin/graphics/ui/Keyboard_White_Arrow_Right.png");
    KeyRightRender->enableBlending();
    KeyRight->addRenderComponent(KeyRightRender);
    uiLayer.add(KeyRight);
    instructionsMenu[9] = KeyRight;

    GameEntity* shoot = new GameEntity();
    TextRenderComponent* shootRender = new TextRenderComponent(shoot, windowElements);
    temp.x = 1*xGrid;
    temp.y = 12*yGrid;
    temp.w = 9*xGrid;
    temp.h = 5*yGrid;
    shootRender->setRenderRect(&temp);
    shootRender->setText("Shoot:", 96);
    shootRender->enableBlending();
    shoot->addRenderComponent(shootRender);
    uiLayer.add(shoot);
    instructionsMenu[10] = shoot;

    GameEntity* keySpace = new GameEntity();
    SpriteRenderComponent* keySpaceRender = new SpriteRenderComponent(keySpace, windowElements);
    temp.x = 13*xGrid;
    temp.y = 12*yGrid;
    temp.w = 8*xGrid;
    temp.h = 6*yGrid;
    keySpaceRender->setRenderRect(&temp);
    keySpaceRender->setImage("bin/graphics/ui/Keyboard_White_Space.png");
    keySpaceRender->enableBlending();
    keySpace->addRenderComponent(keySpaceRender);
    uiLayer.add(keySpace);
    instructionsMenu[11] = keySpace;

    GameEntity* pause = new GameEntity();
    TextRenderComponent* pauseRender = new TextRenderComponent(pause, windowElements);
    temp.x = 1*xGrid;
    temp.y = 18*yGrid;
    temp.w = 9*xGrid;
    temp.h = 5*yGrid;
    pauseRender->setRenderRect(&temp);
    pauseRender->setText("Pause:", 96);
    pauseRender->enableBlending();
    pause->addRenderComponent(pauseRender);
    uiLayer.add(pause);
    instructionsMenu[12] = pause;

    GameEntity* keyP = new GameEntity();
    SpriteRenderComponent* keyPRender = new SpriteRenderComponent(keyP, windowElements);
    temp.x = 15*xGrid;
    temp.y = 18*yGrid;
    temp.w = 5*xGrid;
    temp.h = 5*yGrid;
    keyPRender->setRenderRect(&temp);
    keyPRender->setImage("bin/graphics/ui/Keyboard_White_P.png");
    keyPRender->enableBlending();
    keyP->addRenderComponent(keyPRender);
    uiLayer.add(keyP);
    instructionsMenu[13] = keyP;

    GameEntity* menu = new GameEntity();
    TextRenderComponent* menuRender = new TextRenderComponent(menu, windowElements);
    temp.x = 1*xGrid;
    temp.y = 24*yGrid;
    temp.w = 9*xGrid;
    temp.h = 5*yGrid;
    menuRender->setRenderRect(&temp);
    menuRender->setText("Menu:", 96);
    menuRender->enableBlending();
    menu->addRenderComponent(menuRender);
    uiLayer.add(menu);
    instructionsMenu[14] = menu;

    GameEntity* keyEsc = new GameEntity();
    SpriteRenderComponent* keyEscRender = new SpriteRenderComponent(keyEsc, windowElements);
    temp.x = 15*xGrid;
    temp.y = 24*yGrid;
    temp.w = 5*xGrid;
    temp.h = 5*yGrid;
    keyEscRender->setRenderRect(&temp);
    keyEscRender->setImage("bin/graphics/ui/Keyboard_White_Esc.png");
    keyEscRender->enableBlending();
    keyEsc->addRenderComponent(keyEscRender);
    uiLayer.add(keyEsc);
    instructionsMenu[15] = keyEsc;

    GameEntity* uiBack = new GameEntity();
    UIPanelRenderComponent* uiBackRender = new UIPanelRenderComponent(uiBack, windowElements);
    temp.x = 1*xGrid;
    temp.y = 44*yGrid;
    temp.w = 10*xGrid;
    temp.h = 3*yGrid;
    uiBackRender->setRenderRect(&temp);
    temp.x = 11;
    temp.y = 5;
    temp.w = 80;
    temp.h = 100;
    uiBackRender->addText("Back", 96, &temp, true);
    uiBackRender->enableBlending();
    uiBack->addRenderComponent(uiBackRender);
    UIPanelInputComponent* uiBackInput = new UIPanelInputComponent(uiBack);
    uiBackInput->addClickFunction(new UIClickFunctionBack(state));
    uiBack->addInputComponent(uiBackInput);
    uiLayer.add(uiBack);
    instructionsMenu[16] = uiBack;

    GameEntity* uiControls = new GameEntity();
    UIPanelRenderComponent* uiControlsRender = new UIPanelRenderComponent(uiControls, windowElements);
    temp.x = 23*xGrid;
    temp.y = 12*yGrid;
    temp.w = 34*xGrid;
    temp.h = 34*yGrid;
    uiControlsRender->setRenderRect(&temp);
    uiControlsRender->enableBlending();
    uiControls->addRenderComponent(uiControlsRender);
    uiLayer.add(uiControls);
    instructionsMenu[17] = uiControls;

    std::vector<GameEntity*> instructionsMenuVector(instructionsMenu, instructionsMenu + sizeof(instructionsMenu)/sizeof(GameEntity*));

    return instructionsMenuVector;
}

std::vector<GameEntity*> GameEntityManager::createUICredits(ApplicationState* state)
{
    SDL_Rect temp;
    GameEntity* creditsMenu[5];

    int xGrid = windowElements->WINDOW_WIDTH/60;
    int yGrid = windowElements->WINDOW_HEIGHT/48;

    GameEntity* createdText = new GameEntity();
    TextRenderComponent* createdTextRender = new TextRenderComponent(createdText, windowElements);
    temp.x = 20*xGrid;
    temp.y = 15*yGrid;
    temp.w = 21*xGrid;
    temp.h = 5*yGrid;
    createdTextRender->setRenderRect(&temp);
    createdTextRender->setText("Created by Brandon To", 96);
    createdTextRender->enableBlending();
    createdText->addRenderComponent(createdTextRender);
    uiLayer.add(createdText);
    creditsMenu[0] = createdText;

    GameEntity* developmentText = new GameEntity();
    TextRenderComponent* developmentTextRender = new TextRenderComponent(developmentText, windowElements);
    temp.x = 7*xGrid;
    temp.y = 20*yGrid;
    temp.w = 45*xGrid;
    temp.h = 5*yGrid;
    developmentTextRender->setRenderRect(&temp);
    developmentTextRender->setText("Development of project can be found on Github", 96);
    developmentTextRender->enableBlending();
    developmentText->addRenderComponent(developmentTextRender);
    uiLayer.add(developmentText);
    creditsMenu[1] = developmentText;

    GameEntity* uiFork = new GameEntity();
    UIPanelRenderComponent* uiForkRender = new UIPanelRenderComponent(uiFork, windowElements);
    temp.x = 25*xGrid;
    temp.y = 26*yGrid;
    temp.w = 10*xGrid;
    temp.h = 4*yGrid;
    uiForkRender->setRenderRect(&temp);
    temp.x = 11;
    temp.y = 5;
    temp.w = 80;
    temp.h = 100;
    uiForkRender->addText("Fork Me!", 96, &temp, true);
    uiForkRender->enableBlending();
    uiFork->addRenderComponent(uiForkRender);
    UIPanelInputComponent* uiForkInput = new UIPanelInputComponent(uiFork);
    uiForkInput->addClickFunction(new UIClickFunctionFork(state));
    uiFork->addInputComponent(uiForkInput);
    uiLayer.add(uiFork);
    creditsMenu[2] = uiFork;

    GameEntity* githubText = new GameEntity();
    TextRenderComponent* githubTextRender = new TextRenderComponent(githubText, windowElements);
    temp.x = 23*xGrid;
    temp.y = 32*yGrid;
    temp.w = 14*xGrid;
    temp.h = 2*yGrid;
    githubTextRender->setRenderRect(&temp);
    githubTextRender->setText("https://github.com/brandonto", 96);
    githubTextRender->enableBlending();
    githubText->addRenderComponent(githubTextRender);
    uiLayer.add(githubText);
    creditsMenu[3] = githubText;

    GameEntity* uiBack = new GameEntity();
    UIPanelRenderComponent* uiBackRender = new UIPanelRenderComponent(uiBack, windowElements);
    temp.x = 1*xGrid;
    temp.y = 44*yGrid;
    temp.w = 10*xGrid;
    temp.h = 3*yGrid;
    uiBackRender->setRenderRect(&temp);
    temp.x = 11;
    temp.y = 5;
    temp.w = 80;
    temp.h = 100;
    uiBackRender->addText("Back", 96, &temp, true);
    uiBackRender->enableBlending();
    uiBack->addRenderComponent(uiBackRender);
    UIPanelInputComponent* uiBackInput = new UIPanelInputComponent(uiBack);
    uiBackInput->addClickFunction(new UIClickFunctionBack(state));
    uiBack->addInputComponent(uiBackInput);
    uiLayer.add(uiBack);
    creditsMenu[4] = uiBack;

    std::vector<GameEntity*> creditsMenuVector(creditsMenu, creditsMenu + sizeof(creditsMenu)/sizeof(GameEntity*));

    return creditsMenuVector;
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
