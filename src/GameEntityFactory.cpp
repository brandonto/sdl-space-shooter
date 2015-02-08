/*******************************************************************//*
 * Implementation of the GameEntityFactory class.
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2015-02-07
 * @modified    2015-02-08
 *********************************************************************/
#include "GameEntityFactory.h"

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
#include "GameEntityManager.h"
#include "MeteorPhysicsComponent.h"
#include "MeteorRenderComponent.h"
#include "PlayerCollisionComponent.h"
#include "PlayerInputComponent.h"
#include "PlayerInstructionsInputComponent.h"
#include "PlayerInstructionsPhysicsComponent.h"
#include "PlayerInstructionsProjectilePhysicsComponent.h"
#include "PlayerPhysicsComponent.h"
#include "PlayerRenderComponent.h"
#include "PlayerProjectileCollisionComponent.h"
#include "PlayerProjectilePhysicsComponent.h"
#include "PlayerProjectileRenderComponent.h"
#include "SpriteRenderComponent.h"
#include "TextRenderComponent.h"
#include "UIClickFunction.h"
#include "UIPanelInputComponent.h"
#include "UIPanelRenderComponent.h"
#include "WindowElements.h"

GameEntityFactory::GameEntityFactory(GameEntityManager* gameEntityManager,
                                    WindowElements* windowElements)
:   gameEntityManager(gameEntityManager),
    windowElements(windowElements)
{
    stringToEntityEnum["background"] = ENTITY_BACKGROUND;
    stringToEntityEnum["text"] = ENTITY_TEXT;
    stringToEntityEnum["uiPanel"] = ENTITY_UIPANEL;
}

GameEntityFactory::~GameEntityFactory()
{

}

std::vector<GameEntity*> GameEntityFactory::createBackgroundEntities()
{
    std::vector<EntityXmlStruct> xmlStructs = xmlParser.parse(gameEntityManager->getState(), PARSE_BACKGROUND);
    GameEntity* background[1];
    background[0] = createBackground();
    std::vector<GameEntity*> backgroundVector(background, background + sizeof(background)/sizeof(GameEntity*));
    return backgroundVector;
}

std::vector<GameEntity*> GameEntityFactory::createPhysicalEntities()
{
    //xmlParser.parse(gameEntityManager->getState(), PARSE_PHYSICAL);
}

std::vector<GameEntity*> GameEntityFactory::createEffectEntities()
{
    //xmlParser.parse(gameEntityManager->getState(), PARSE_EFFECT);
}

std::vector<GameEntity*> GameEntityFactory::createUIEntities()
{
    std::vector<EntityXmlStruct> xmlStructs = xmlParser.parse(gameEntityManager->getState(), PARSE_UI);
    int numEntities = xmlStructs.size();

    GameEntity* ui[numEntities];

    for (int i=0; i<numEntities; i++)
    {
        ui[i] = createEntity(xmlStructs[i]);
    }

    std::vector<GameEntity*> uiVector(ui, ui + sizeof(ui)/sizeof(GameEntity*));
    return uiVector;
}

GameEntity* GameEntityFactory::createEntity(EntityXmlStruct xmlStruct)
{
    GameEntity* entity = new GameEntity();

    switch (stringToEntityEnum[xmlStruct.type])
    {
        case ENTITY_BACKGROUND:
        {
            entity->addRenderComponent(new BackgroundRenderComponent(entity, windowElements));
            entity->addPhysicsComponent(new BackgroundPhysicsComponent(entity, windowElements));
            configureEntity(entity, xmlStruct);
            gameEntityManager->addBackgroundEntity(entity);
            break;
        }

        case ENTITY_TEXT:
        {
            TextRenderComponent* entityRender = new TextRenderComponent(entity, windowElements);
            entityRender->setText(xmlStruct.data, 96);
            entity->addRenderComponent(entityRender);
            configureEntity(entity, xmlStruct);
            gameEntityManager->addUIEntity(entity);
            break;
        }

        case ENTITY_UIPANEL:
        {
            UIPanelRenderComponent* entityRender = new UIPanelRenderComponent(entity, windowElements);
            entity->addRenderComponent(entityRender);
            if (xmlStruct.function != "NONE")
            {
                UIPanelInputComponent* entityInput = new UIPanelInputComponent(entity);
                //entityInput->addClickFunction(new UIClickFunctionPlay(state));
                entity->addInputComponent(entityInput);
            }
            configureEntity(entity, xmlStruct);
            gameEntityManager->addUIEntity(entity);
            break;
        }

        default:
            fprintf(stderr, "[ERROR] createEntity(): unknown type.\n");
            delete entity;
            entity = NULL;
            break;
    }

    return entity;
}

// Configures entity using the data passed in xmlStruct
void GameEntityFactory::configureEntity(GameEntity* entity, EntityXmlStruct xmlStruct)
{
    entity->setID(xmlStruct.id);
    entity->setName(xmlStruct.name);
    entity->setType(xmlStruct.type);
    // Only sets texture if there was one specified, otherwise use the default
    if (xmlStruct.texture != "")
    {
        entity->getRenderComponent()->getTexture()->setTexture(xmlStruct.texture);
    }
    entity->getRenderComponent()->setRenderRect(&(xmlStruct.renderRect));
    if (xmlStruct.alphaEnabled)
    {
        entity->getRenderComponent()->getTexture()->enableAlphaBlend();
    }
}

std::vector<GameEntity*> GameEntityFactory::createMainMenu(ApplicationState* state)
{
    SDL_Rect temp;
    GameEntity* mainMenu[13];

    int xGrid = windowElements->WINDOW_WIDTH/30;
    int yGrid = windowElements->WINDOW_HEIGHT/48;

    GameEntity* uiTitle = new GameEntity();
    UIPanelRenderComponent* uiTitleRender = new UIPanelRenderComponent(uiTitle, windowElements);
    temp.x = 6*xGrid;
    temp.y = 6*yGrid;
    temp.w = 18*xGrid;
    temp.h = 12*yGrid;
    uiTitleRender->setRenderRect(&temp);
    uiTitleRender->getTexture()->enableAlphaBlend();
    uiTitle->addRenderComponent(uiTitleRender);
    gameEntityManager->addUIEntity(uiTitle);
    mainMenu[0] = uiTitle;

    GameEntity* spaceText = new GameEntity();
    TextRenderComponent* spaceTextRender = new TextRenderComponent(spaceText, windowElements);
    temp.x = 6*xGrid+30;
    temp.y = 6*yGrid+2;
    temp.w = 18*xGrid-45;
    temp.h = 6*yGrid-5;
    spaceTextRender->setRenderRect(&temp);
    spaceTextRender->setText("Space", 96);
    spaceTextRender->getTexture()->enableAlphaBlend();
    spaceText->addRenderComponent(spaceTextRender);
    gameEntityManager->addUIEntity(spaceText);
    mainMenu[1] = spaceText;

    GameEntity* shooterText = new GameEntity();
    TextRenderComponent* shooterTextRender = new TextRenderComponent(shooterText, windowElements);
    temp.x = 6*xGrid+30;
    temp.y = 12*yGrid+2;
    temp.w = 18*xGrid-45;
    temp.h = 6*yGrid-5;
    shooterTextRender->setRenderRect(&temp);
    shooterTextRender->setText("Shooter", 96);
    shooterTextRender->getTexture()->enableAlphaBlend();
    shooterText->addRenderComponent(shooterTextRender);
    gameEntityManager->addUIEntity(shooterText);
    mainMenu[2] = shooterText;

    GameEntity* uiPlay = new GameEntity();
    UIPanelRenderComponent* uiPlayRender = new UIPanelRenderComponent(uiPlay, windowElements);
    temp.x = 10*xGrid;
    temp.y = 21*yGrid;
    temp.w = 10*xGrid;
    temp.h = 3*yGrid;
    uiPlayRender->setRenderRect(&temp);
    uiPlayRender->getTexture()->enableAlphaBlend();
    uiPlay->addRenderComponent(uiPlayRender);
    UIPanelInputComponent* uiPlayInput = new UIPanelInputComponent(uiPlay);
    uiPlayInput->addClickFunction(new UIClickFunctionPlay(state));
    uiPlay->addInputComponent(uiPlayInput);
    gameEntityManager->addUIEntity(uiPlay);
    mainMenu[3] = uiPlay;

    GameEntity* playText = new GameEntity();
    TextRenderComponent* playTextRender = new TextRenderComponent(playText, windowElements);
    temp.x = 10*xGrid+18;
    temp.y = 21*yGrid+2;
    temp.w = 10*xGrid-25;
    temp.h = 3*yGrid-5;
    playTextRender->setRenderRect(&temp);
    playTextRender->setText("Play", 96);
    playTextRender->getTexture()->enableAlphaBlend();
    playText->addRenderComponent(playTextRender);
    gameEntityManager->addUIEntity(playText);
    mainMenu[4] = playText;

    GameEntity* uiInstructions = new GameEntity();
    UIPanelRenderComponent* uiInstructionsRender = new UIPanelRenderComponent(uiInstructions, windowElements);
    temp.x = 10*xGrid;
    temp.y = 26*yGrid;
    temp.w = 10*xGrid;
    temp.h = 3*yGrid;
    uiInstructionsRender->setRenderRect(&temp);
    uiInstructionsRender->getTexture()->enableAlphaBlend();
    uiInstructions->addRenderComponent(uiInstructionsRender);
    UIPanelInputComponent* uiInstructionsInput = new UIPanelInputComponent(uiInstructions);
    uiInstructionsInput->addClickFunction(new UIClickFunctionInstructions(state));
    uiInstructions->addInputComponent(uiInstructionsInput);
    gameEntityManager->addUIEntity(uiInstructions);
    mainMenu[5] = uiInstructions;

    GameEntity* instructionsText = new GameEntity();
    TextRenderComponent* instructionsTextRender = new TextRenderComponent(instructionsText, windowElements);
    temp.x = 10*xGrid+18;
    temp.y = 26*yGrid+2;
    temp.w = 10*xGrid-25;
    temp.h = 3*yGrid-5;
    instructionsTextRender->setRenderRect(&temp);
    instructionsTextRender->setText("Instructions", 96);
    instructionsTextRender->getTexture()->enableAlphaBlend();
    instructionsText->addRenderComponent(instructionsTextRender);
    gameEntityManager->addUIEntity(instructionsText);
    mainMenu[6] = instructionsText;

    GameEntity* uiOptions = new GameEntity();
    UIPanelRenderComponent* uiOptionsRender = new UIPanelRenderComponent(uiOptions, windowElements);
    temp.x = 10*xGrid;
    temp.y = 31*yGrid;
    temp.w = 10*xGrid;
    temp.h = 3*yGrid;
    uiOptionsRender->setRenderRect(&temp);
    uiOptionsRender->getTexture()->enableAlphaBlend();
    uiOptions->addRenderComponent(uiOptionsRender);
    UIPanelInputComponent* uiOptionsInput = new UIPanelInputComponent(uiOptions);
    uiOptions->addInputComponent(uiOptionsInput);
    gameEntityManager->addUIEntity(uiOptions);
    mainMenu[7] = uiOptions;

    GameEntity* optionsText = new GameEntity();
    TextRenderComponent* optionsTextRender = new TextRenderComponent(optionsText, windowElements);
    temp.x = 10*xGrid+18;
    temp.y = 31*yGrid+2;
    temp.w = 10*xGrid-25;
    temp.h = 3*yGrid-5;
    optionsTextRender->setRenderRect(&temp);
    optionsTextRender->setText("Options", 96);
    optionsTextRender->getTexture()->enableAlphaBlend();
    optionsText->addRenderComponent(optionsTextRender);
    gameEntityManager->addUIEntity(optionsText);
    mainMenu[8] = optionsText;

    GameEntity* uiCredits = new GameEntity();
    UIPanelRenderComponent* uiCreditsRender = new UIPanelRenderComponent(uiCredits, windowElements);
    temp.x = 10*xGrid;
    temp.y = 36*yGrid;
    temp.w = 10*xGrid;
    temp.h = 3*yGrid;
    uiCreditsRender->setRenderRect(&temp);
    uiCreditsRender->getTexture()->enableAlphaBlend();
    uiCredits->addRenderComponent(uiCreditsRender);
    UIPanelInputComponent* uiCreditsInput = new UIPanelInputComponent(uiCredits);
    uiCreditsInput->addClickFunction(new UIClickFunctionCredits(state));
    uiCredits->addInputComponent(uiCreditsInput);
    gameEntityManager->addUIEntity(uiCredits);
    mainMenu[9] = uiCredits;

    GameEntity* creditsText = new GameEntity();
    TextRenderComponent* creditsTextRender = new TextRenderComponent(creditsText, windowElements);
    temp.x = 10*xGrid+18;
    temp.y = 36*yGrid+2;
    temp.w = 10*xGrid-25;
    temp.h = 3*yGrid-5;
    creditsTextRender->setRenderRect(&temp);
    creditsTextRender->setText("Credits", 96);
    creditsTextRender->getTexture()->enableAlphaBlend();
    creditsText->addRenderComponent(creditsTextRender);
    gameEntityManager->addUIEntity(creditsText);
    mainMenu[10] = creditsText;

    GameEntity* uiQuit = new GameEntity();
    UIPanelRenderComponent* uiQuitRender = new UIPanelRenderComponent(uiQuit, windowElements);
    temp.x = 10*xGrid;
    temp.y = 41*yGrid;
    temp.w = 10*xGrid;
    temp.h = 3*yGrid;
    uiQuitRender->setRenderRect(&temp);
    uiQuitRender->getTexture()->enableAlphaBlend();
    uiQuit->addRenderComponent(uiQuitRender);
    UIPanelInputComponent* uiQuitInput = new UIPanelInputComponent(uiQuit);
    uiQuitInput->addClickFunction(new UIClickFunctionQuit(state));
    uiQuit->addInputComponent(uiQuitInput);
    gameEntityManager->addUIEntity(uiQuit);
    mainMenu[11] = uiQuit;

    GameEntity* quitText = new GameEntity();
    TextRenderComponent* quitTextRender = new TextRenderComponent(quitText, windowElements);
    temp.x = 10*xGrid+18;
    temp.y = 41*yGrid+2;
    temp.w = 10*xGrid-25;
    temp.h = 3*yGrid-5;
    quitTextRender->setRenderRect(&temp);
    quitTextRender->setText("Quit", 96);
    quitTextRender->getTexture()->enableAlphaBlend();
    quitText->addRenderComponent(quitTextRender);
    gameEntityManager->addUIEntity(quitText);
    mainMenu[12] = quitText;

    std::vector<GameEntity*> mainMenuVector(mainMenu, mainMenu + sizeof(mainMenu)/sizeof(GameEntity*));

    return mainMenuVector;
}

std::vector<GameEntity*> GameEntityFactory::createUIInstructions(ApplicationState* state)
{
    SDL_Rect temp;
    GameEntity* instructionsMenu[19];

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
    movementTextRender->getTexture()->enableAlphaBlend();
    movementText->addRenderComponent(movementTextRender);
    gameEntityManager->addUIEntity(movementText);
    instructionsMenu[0] = movementText;

    GameEntity* keyW = new GameEntity();
    SpriteRenderComponent* keyWRender = new SpriteRenderComponent(keyW, windowElements);
    temp.x = 21*xGrid;
    temp.y = 2*yGrid;
    temp.w = 5*xGrid;
    temp.h = 5*yGrid;
    keyWRender->setRenderRect(&temp);
    keyWRender->getTexture()->setTexture("bin/graphics/ui/Keyboard_White_W.png");
    keyWRender->getTexture()->enableAlphaBlend();
    keyW->addRenderComponent(keyWRender);
    gameEntityManager->addUIEntity(keyW);
    instructionsMenu[1] = keyW;

    GameEntity* keyA = new GameEntity();
    SpriteRenderComponent* keyARender = new SpriteRenderComponent(keyA, windowElements);
    temp.x = 17*xGrid;
    temp.y = 6*yGrid;
    temp.w = 5*xGrid;
    temp.h = 5*yGrid;
    keyARender->setRenderRect(&temp);
    keyARender->getTexture()->setTexture("bin/graphics/ui/Keyboard_White_A.png");
    keyARender->getTexture()->enableAlphaBlend();
    keyA->addRenderComponent(keyARender);
    gameEntityManager->addUIEntity(keyA);
    instructionsMenu[2] = keyA;

    GameEntity* keyS = new GameEntity();
    SpriteRenderComponent* keySRender = new SpriteRenderComponent(keyS, windowElements);
    temp.x = 21*xGrid;
    temp.y = 6*yGrid;
    temp.w = 5*xGrid;
    temp.h = 5*yGrid;
    keySRender->setRenderRect(&temp);
    keySRender->getTexture()->setTexture("bin/graphics/ui/Keyboard_White_S.png");
    keySRender->getTexture()->enableAlphaBlend();
    keyS->addRenderComponent(keySRender);
    gameEntityManager->addUIEntity(keyS);
    instructionsMenu[3] = keyS;

    GameEntity* keyD = new GameEntity();
    SpriteRenderComponent* keyDRender = new SpriteRenderComponent(keyD, windowElements);
    temp.x = 25*xGrid;
    temp.y = 6*yGrid;
    temp.w = 5*xGrid;
    temp.h = 5*yGrid;
    keyDRender->setRenderRect(&temp);
    keyDRender->getTexture()->setTexture("bin/graphics/ui/Keyboard_White_D.png");
    keyDRender->getTexture()->enableAlphaBlend();
    keyD->addRenderComponent(keyDRender);
    gameEntityManager->addUIEntity(keyD);
    instructionsMenu[4] = keyD;

    GameEntity* orText = new GameEntity();
    TextRenderComponent* orTextRender = new TextRenderComponent(orText, windowElements);
    temp.x = 35*xGrid;
    temp.y = 4*yGrid;
    temp.w = 2*xGrid;
    temp.h = 5*yGrid;
    orTextRender->setRenderRect(&temp);
    orTextRender->setText("or", 96);
    orTextRender->getTexture()->enableAlphaBlend();
    orText->addRenderComponent(orTextRender);
    gameEntityManager->addUIEntity(orText);
    instructionsMenu[5] = orText;

    GameEntity* keyUp = new GameEntity();
    SpriteRenderComponent* keyUpRender = new SpriteRenderComponent(keyUp, windowElements);
    temp.x = 46*xGrid;
    temp.y = 2*yGrid;
    temp.w = 5*xGrid;
    temp.h = 5*yGrid;
    keyUpRender->setRenderRect(&temp);
    keyUpRender->getTexture()->setTexture("bin/graphics/ui/Keyboard_White_Arrow_Up.png");
    keyUpRender->getTexture()->enableAlphaBlend();
    keyUp->addRenderComponent(keyUpRender);
    gameEntityManager->addUIEntity(keyUp);
    instructionsMenu[6] = keyUp;

    GameEntity* keyLeft = new GameEntity();
    SpriteRenderComponent* keyLeftRender = new SpriteRenderComponent(keyLeft, windowElements);
    temp.x = 42*xGrid;
    temp.y = 6*yGrid;
    temp.w = 5*xGrid;
    temp.h = 5*yGrid;
    keyLeftRender->setRenderRect(&temp);
    keyLeftRender->getTexture()->setTexture("bin/graphics/ui/Keyboard_White_Arrow_Left.png");
    keyLeftRender->getTexture()->enableAlphaBlend();
    keyLeft->addRenderComponent(keyLeftRender);
    gameEntityManager->addUIEntity(keyLeft);
    instructionsMenu[7] = keyLeft;

    GameEntity* keyDown = new GameEntity();
    SpriteRenderComponent* keyDownRender = new SpriteRenderComponent(keyDown, windowElements);
    temp.x = 46*xGrid;
    temp.y = 6*yGrid;
    temp.w = 5*xGrid;
    temp.h = 5*yGrid;
    keyDownRender->setRenderRect(&temp);
    keyDownRender->getTexture()->setTexture("bin/graphics/ui/Keyboard_White_Arrow_Down.png");
    keyDownRender->getTexture()->enableAlphaBlend();
    keyDown->addRenderComponent(keyDownRender);
    gameEntityManager->addUIEntity(keyDown);
    instructionsMenu[8] = keyDown;

    GameEntity* KeyRight = new GameEntity();
    SpriteRenderComponent* KeyRightRender = new SpriteRenderComponent(KeyRight, windowElements);
    temp.x = 50*xGrid;
    temp.y = 6*yGrid;
    temp.w = 5*xGrid;
    temp.h = 5*yGrid;
    KeyRightRender->setRenderRect(&temp);
    KeyRightRender->getTexture()->setTexture("bin/graphics/ui/Keyboard_White_Arrow_Right.png");
    KeyRightRender->getTexture()->enableAlphaBlend();
    KeyRight->addRenderComponent(KeyRightRender);
    gameEntityManager->addUIEntity(KeyRight);
    instructionsMenu[9] = KeyRight;

    GameEntity* shoot = new GameEntity();
    TextRenderComponent* shootRender = new TextRenderComponent(shoot, windowElements);
    temp.x = 1*xGrid;
    temp.y = 12*yGrid;
    temp.w = 9*xGrid;
    temp.h = 5*yGrid;
    shootRender->setRenderRect(&temp);
    shootRender->setText("Shoot:", 96);
    shootRender->getTexture()->enableAlphaBlend();
    shoot->addRenderComponent(shootRender);
    gameEntityManager->addUIEntity(shoot);
    instructionsMenu[10] = shoot;

    GameEntity* keySpace = new GameEntity();
    SpriteRenderComponent* keySpaceRender = new SpriteRenderComponent(keySpace, windowElements);
    temp.x = 13*xGrid;
    temp.y = 12*yGrid;
    temp.w = 8*xGrid;
    temp.h = 6*yGrid;
    keySpaceRender->setRenderRect(&temp);
    keySpaceRender->getTexture()->setTexture("bin/graphics/ui/Keyboard_White_Space.png");
    keySpaceRender->getTexture()->enableAlphaBlend();
    keySpace->addRenderComponent(keySpaceRender);
    gameEntityManager->addUIEntity(keySpace);
    instructionsMenu[11] = keySpace;

    GameEntity* pause = new GameEntity();
    TextRenderComponent* pauseRender = new TextRenderComponent(pause, windowElements);
    temp.x = 1*xGrid;
    temp.y = 18*yGrid;
    temp.w = 9*xGrid;
    temp.h = 5*yGrid;
    pauseRender->setRenderRect(&temp);
    pauseRender->setText("Pause:", 96);
    pauseRender->getTexture()->enableAlphaBlend();
    pause->addRenderComponent(pauseRender);
    gameEntityManager->addUIEntity(pause);
    instructionsMenu[12] = pause;

    GameEntity* keyP = new GameEntity();
    SpriteRenderComponent* keyPRender = new SpriteRenderComponent(keyP, windowElements);
    temp.x = 15*xGrid;
    temp.y = 18*yGrid;
    temp.w = 5*xGrid;
    temp.h = 5*yGrid;
    keyPRender->setRenderRect(&temp);
    keyPRender->getTexture()->setTexture("bin/graphics/ui/Keyboard_White_P.png");
    keyPRender->getTexture()->enableAlphaBlend();
    keyP->addRenderComponent(keyPRender);
    gameEntityManager->addUIEntity(keyP);
    instructionsMenu[13] = keyP;

    GameEntity* menu = new GameEntity();
    TextRenderComponent* menuRender = new TextRenderComponent(menu, windowElements);
    temp.x = 1*xGrid;
    temp.y = 24*yGrid;
    temp.w = 9*xGrid;
    temp.h = 5*yGrid;
    menuRender->setRenderRect(&temp);
    menuRender->setText("Menu:", 96);
    menuRender->getTexture()->enableAlphaBlend();
    menu->addRenderComponent(menuRender);
    gameEntityManager->addUIEntity(menu);
    instructionsMenu[14] = menu;

    GameEntity* keyEsc = new GameEntity();
    SpriteRenderComponent* keyEscRender = new SpriteRenderComponent(keyEsc, windowElements);
    temp.x = 15*xGrid;
    temp.y = 24*yGrid;
    temp.w = 5*xGrid;
    temp.h = 5*yGrid;
    keyEscRender->setRenderRect(&temp);
    keyEscRender->getTexture()->setTexture("bin/graphics/ui/Keyboard_White_Esc.png");
    keyEscRender->getTexture()->enableAlphaBlend();
    keyEsc->addRenderComponent(keyEscRender);
    gameEntityManager->addUIEntity(keyEsc);
    instructionsMenu[15] = keyEsc;

    GameEntity* uiBack = new GameEntity();
    UIPanelRenderComponent* uiBackRender = new UIPanelRenderComponent(uiBack, windowElements);
    temp.x = 1*xGrid;
    temp.y = 44*yGrid;
    temp.w = 10*xGrid;
    temp.h = 3*yGrid;
    uiBackRender->setRenderRect(&temp);
    uiBackRender->getTexture()->enableAlphaBlend();
    uiBack->addRenderComponent(uiBackRender);
    UIPanelInputComponent* uiBackInput = new UIPanelInputComponent(uiBack);
    uiBackInput->addClickFunction(new UIClickFunctionBack(state));
    uiBack->addInputComponent(uiBackInput);
    gameEntityManager->addUIEntity(uiBack);
    instructionsMenu[16] = uiBack;

    GameEntity* backText = new GameEntity();
    TextRenderComponent* backTextRender = new TextRenderComponent(backText, windowElements);
    temp.x = 1*xGrid+10;
    temp.y = 44*yGrid+1;
    temp.w = 10*xGrid-15;
    temp.h = 3*yGrid-1;
    backTextRender->setRenderRect(&temp);
    backTextRender->setText("Back", 96);
    backTextRender->getTexture()->enableAlphaBlend();
    backText->addRenderComponent(backTextRender);
    gameEntityManager->addUIEntity(backText);
    instructionsMenu[17] = backText;

    GameEntity* uiControls = new GameEntity();
    UIPanelRenderComponent* uiControlsRender = new UIPanelRenderComponent(uiControls, windowElements);
    temp.x = 23*xGrid;
    temp.y = 12*yGrid;
    temp.w = 34*xGrid;
    temp.h = 34*yGrid;
    uiControlsRender->setRenderRect(&temp);
    uiControlsRender->getTexture()->enableAlphaBlend();
    uiControls->addRenderComponent(uiControlsRender);
    gameEntityManager->addUIEntity(uiControls);
    instructionsMenu[18] = uiControls;

    std::vector<GameEntity*> instructionsMenuVector(instructionsMenu, instructionsMenu + sizeof(instructionsMenu)/sizeof(GameEntity*));

    return instructionsMenuVector;
}

std::vector<GameEntity*> GameEntityFactory::createUICredits(ApplicationState* state)
{
    SDL_Rect temp;
    GameEntity* creditsMenu[7];

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
    createdTextRender->getTexture()->enableAlphaBlend();
    createdText->addRenderComponent(createdTextRender);
    gameEntityManager->addUIEntity(createdText);
    creditsMenu[0] = createdText;

    GameEntity* developmentText = new GameEntity();
    TextRenderComponent* developmentTextRender = new TextRenderComponent(developmentText, windowElements);
    temp.x = 7*xGrid;
    temp.y = 20*yGrid;
    temp.w = 45*xGrid;
    temp.h = 5*yGrid;
    developmentTextRender->setRenderRect(&temp);
    developmentTextRender->setText("Development of project can be found on Github", 96);
    developmentTextRender->getTexture()->enableAlphaBlend();
    developmentText->addRenderComponent(developmentTextRender);
    gameEntityManager->addUIEntity(developmentText);
    creditsMenu[1] = developmentText;

    GameEntity* uiFork = new GameEntity();
    UIPanelRenderComponent* uiForkRender = new UIPanelRenderComponent(uiFork, windowElements);
    temp.x = 25*xGrid;
    temp.y = 26*yGrid;
    temp.w = 10*xGrid;
    temp.h = 4*yGrid;
    uiForkRender->setRenderRect(&temp);
    uiForkRender->getTexture()->enableAlphaBlend();
    uiFork->addRenderComponent(uiForkRender);
    UIPanelInputComponent* uiForkInput = new UIPanelInputComponent(uiFork);
    uiForkInput->addClickFunction(new UIClickFunctionFork(state));
    uiFork->addInputComponent(uiForkInput);
    gameEntityManager->addUIEntity(uiFork);
    creditsMenu[2] = uiFork;

    GameEntity* forkText = new GameEntity();
    TextRenderComponent* forkTextRender = new TextRenderComponent(forkText, windowElements);
    temp.x = 25*xGrid+10;
    temp.y = 26*yGrid+1;
    temp.w = 10*xGrid-15;
    temp.h = 4*yGrid-1;
    forkTextRender->setRenderRect(&temp);
    forkTextRender->setText("Fork Me!", 96);
    forkTextRender->getTexture()->enableAlphaBlend();
    forkText->addRenderComponent(forkTextRender);
    gameEntityManager->addUIEntity(forkText);
    creditsMenu[3] = forkText;

    GameEntity* githubText = new GameEntity();
    TextRenderComponent* githubTextRender = new TextRenderComponent(githubText, windowElements);
    temp.x = 23*xGrid;
    temp.y = 32*yGrid;
    temp.w = 14*xGrid;
    temp.h = 2*yGrid;
    githubTextRender->setRenderRect(&temp);
    githubTextRender->setText("https://github.com/brandonto", 96);
    githubTextRender->getTexture()->enableAlphaBlend();
    githubText->addRenderComponent(githubTextRender);
    gameEntityManager->addUIEntity(githubText);
    creditsMenu[4] = githubText;

    GameEntity* uiBack = new GameEntity();
    UIPanelRenderComponent* uiBackRender = new UIPanelRenderComponent(uiBack, windowElements);
    temp.x = 1*xGrid;
    temp.y = 44*yGrid;
    temp.w = 10*xGrid;
    temp.h = 3*yGrid;
    uiBackRender->setRenderRect(&temp);
    uiBackRender->getTexture()->enableAlphaBlend();
    uiBack->addRenderComponent(uiBackRender);
    UIPanelInputComponent* uiBackInput = new UIPanelInputComponent(uiBack);
    uiBackInput->addClickFunction(new UIClickFunctionBack(state));
    uiBack->addInputComponent(uiBackInput);
    gameEntityManager->addUIEntity(uiBack);
    creditsMenu[5] = uiBack;

    GameEntity* backText = new GameEntity();
    TextRenderComponent* backTextRender = new TextRenderComponent(backText, windowElements);
    temp.x = 1*xGrid+10;
    temp.y = 44*yGrid+1;
    temp.w = 10*xGrid-15;
    temp.h = 3*yGrid-1;
    backTextRender->setRenderRect(&temp);
    backTextRender->setText("Back", 96);
    backTextRender->getTexture()->enableAlphaBlend();
    backText->addRenderComponent(backTextRender);
    gameEntityManager->addUIEntity(backText);
    creditsMenu[6] = backText;

    std::vector<GameEntity*> creditsMenuVector(creditsMenu, creditsMenu + sizeof(creditsMenu)/sizeof(GameEntity*));

    return creditsMenuVector;
}

std::vector<GameEntity*> GameEntityFactory::createGameMenu(ApplicationState* state)
{
    SDL_Rect temp;
    GameEntity* gameMenu[9];

    int xGrid = windowElements->WINDOW_WIDTH/60;
    int yGrid = windowElements->WINDOW_HEIGHT/48;

    GameEntity* uiPanel = new GameEntity();
    UIPanelRenderComponent* uiPanelRender = new UIPanelRenderComponent(uiPanel, windowElements);
    temp.x = 15*xGrid;
    temp.y = 9*yGrid;
    temp.w = 30*xGrid;
    temp.h = 30*yGrid;
    uiPanelRender->setRenderRect(&temp);
    uiPanelRender->getTexture()->enableAlphaBlend();
    uiPanel->addRenderComponent(uiPanelRender);
    gameEntityManager->addUIEntity(uiPanel);
    gameMenu[0] = uiPanel;

    GameEntity* uiResume = new GameEntity();
    UIPanelRenderComponent* uiResumeRender = new UIPanelRenderComponent(uiResume, windowElements);
    temp.x = 20*xGrid;
    temp.y = 14*yGrid;
    temp.w = 20*xGrid;
    temp.h = 3*yGrid;
    uiResumeRender->setRenderRect(&temp);
    uiResumeRender->getTexture()->enableAlphaBlend();
    uiResume->addRenderComponent(uiResumeRender);
    UIPanelInputComponent* uiResumeInput = new UIPanelInputComponent(uiResume);
    uiResumeInput->addClickFunction(new UIClickFunctionResume(state));
    uiResume->addInputComponent(uiResumeInput);
    gameEntityManager->addUIEntity(uiResume);
    gameMenu[1] = uiResume;

    GameEntity* resumeText = new GameEntity();
    TextRenderComponent* resumeTextRender = new TextRenderComponent(resumeText, windowElements);
    temp.x = 20*xGrid+15;
    temp.y = 14*yGrid+5;
    temp.w = 20*xGrid-25;
    temp.h = 3*yGrid-5;
    resumeTextRender->setRenderRect(&temp);
    resumeTextRender->setText("Resume", 96);
    resumeTextRender->getTexture()->enableAlphaBlend();
    resumeText->addRenderComponent(resumeTextRender);
    gameEntityManager->addUIEntity(resumeText);
    gameMenu[2] = resumeText;

    GameEntity* uiOptions = new GameEntity();
    UIPanelRenderComponent* uiOptionsRender = new UIPanelRenderComponent(uiOptions, windowElements);
    temp.x = 20*xGrid;
    temp.y = 19*yGrid;
    temp.w = 20*xGrid;
    temp.h = 3*yGrid;
    uiOptionsRender->setRenderRect(&temp);
    uiOptionsRender->getTexture()->enableAlphaBlend();
    uiOptions->addRenderComponent(uiOptionsRender);
    UIPanelInputComponent* uiOptionsInput = new UIPanelInputComponent(uiOptions);
    uiOptions->addInputComponent(uiOptionsInput);
    gameEntityManager->addUIEntity(uiOptions);
    gameMenu[3] = uiOptions;

    GameEntity* optionsText = new GameEntity();
    TextRenderComponent* optionsTextRender = new TextRenderComponent(optionsText, windowElements);
    temp.x = 20*xGrid+15;
    temp.y = 19*yGrid+5;
    temp.w = 20*xGrid-25;
    temp.h = 3*yGrid-5;
    optionsTextRender->setRenderRect(&temp);
    optionsTextRender->setText("Options", 96);
    optionsTextRender->getTexture()->enableAlphaBlend();
    optionsText->addRenderComponent(optionsTextRender);
    gameEntityManager->addUIEntity(optionsText);
    gameMenu[4] = optionsText;

    GameEntity* uiMainMenu = new GameEntity();
    UIPanelRenderComponent* uiMainMenuRender = new UIPanelRenderComponent(uiMainMenu, windowElements);
    temp.x = 20*xGrid;
    temp.y = 24*yGrid;
    temp.w = 20*xGrid;
    temp.h = 3*yGrid;
    uiMainMenuRender->setRenderRect(&temp);
    uiMainMenuRender->getTexture()->enableAlphaBlend();
    uiMainMenu->addRenderComponent(uiMainMenuRender);
    UIPanelInputComponent* uiMainMenuInput = new UIPanelInputComponent(uiMainMenu);
    uiMainMenuInput->addClickFunction(new UIClickFunctionMenu(state));
    uiMainMenu->addInputComponent(uiMainMenuInput);
    gameEntityManager->addUIEntity(uiMainMenu);
    gameMenu[5] = uiMainMenu;

    GameEntity* mainMenuText = new GameEntity();
    TextRenderComponent* mainMenuTextRender = new TextRenderComponent(mainMenuText, windowElements);
    temp.x = 20*xGrid+15;
    temp.y = 24*yGrid+5;
    temp.w = 20*xGrid-25;
    temp.h = 3*yGrid-5;
    mainMenuTextRender->setRenderRect(&temp);
    mainMenuTextRender->setText("Main Menu", 96);
    mainMenuTextRender->getTexture()->enableAlphaBlend();
    mainMenuText->addRenderComponent(mainMenuTextRender);
    gameEntityManager->addUIEntity(mainMenuText);
    gameMenu[6] = mainMenuText;

    GameEntity* uiQuit = new GameEntity();
    UIPanelRenderComponent* uiQuitRender = new UIPanelRenderComponent(uiQuit, windowElements);
    temp.x = 20*xGrid;
    temp.y = 29*yGrid;
    temp.w = 20*xGrid;
    temp.h = 3*yGrid;
    uiQuitRender->setRenderRect(&temp);
    uiQuitRender->getTexture()->enableAlphaBlend();
    uiQuit->addRenderComponent(uiQuitRender);
    UIPanelInputComponent* uiQuitInput = new UIPanelInputComponent(uiQuit);
    uiQuitInput->addClickFunction(new UIClickFunctionQuit(state));
    uiQuit->addInputComponent(uiQuitInput);
    gameEntityManager->addUIEntity(uiQuit);
    gameMenu[7] = uiQuit;

    GameEntity* quitText = new GameEntity();
    TextRenderComponent* quitTextRender = new TextRenderComponent(quitText, windowElements);
    temp.x = 20*xGrid+15;
    temp.y = 29*yGrid+5;
    temp.w = 20*xGrid-25;
    temp.h = 3*yGrid-5;
    quitTextRender->setRenderRect(&temp);
    quitTextRender->setText("Quit", 96);
    quitTextRender->getTexture()->enableAlphaBlend();
    quitText->addRenderComponent(quitTextRender);
    gameEntityManager->addUIEntity(quitText);
    gameMenu[8] = quitText;

    std::vector<GameEntity*> gameMenuVector(gameMenu, gameMenu + sizeof(gameMenu)/sizeof(GameEntity*));

    return gameMenuVector;
}

GameEntity* GameEntityFactory::createBackground()
{
    GameEntity* background = new GameEntity();
    background->addRenderComponent(new BackgroundRenderComponent(background, windowElements));
    background->addPhysicsComponent(new BackgroundPhysicsComponent(background, windowElements));
    gameEntityManager->addBackgroundEntity(background);

    return background;
}

GameEntity* GameEntityFactory::createEnemy()
{
    GameEntity* enemy = new GameEntity();
    enemy->addRenderComponent(new EnemyRenderComponent(enemy, windowElements));
    enemy->addPhysicsComponent(new EnemyPhysicsComponent(enemy, windowElements, this));
    enemy->addCollisionComponent(new EnemyCollisionComponent(enemy, windowElements, gameEntityManager->getCollisionManager()));
    gameEntityManager->addPhysicalEntity(enemy);

    return enemy;
}

GameEntity* GameEntityFactory::createEnemyProjectile(GameEntity* enemyEntity)
{
    GameEntity* projectile = new GameEntity();
    projectile->addRenderComponent(new EnemyProjectileRenderComponent(projectile, windowElements, enemyEntity));
    projectile->addPhysicsComponent(new EnemyProjectilePhysicsComponent(projectile, windowElements));
    projectile->addCollisionComponent(new EnemyProjectileCollisionComponent(projectile, windowElements, gameEntityManager->getCollisionManager()));
    gameEntityManager->addPhysicalEntity(projectile);

    return projectile;
}

std::vector<GameEntity*> GameEntityFactory::createEnemyWaveStraight2()
{
    GameEntity* enemyWave[2];

    enemyWave[0] = createEnemy();
    enemyWave[0]->position.x = windowElements->WINDOW_WIDTH/3;

    enemyWave[1] = createEnemy();
    enemyWave[1]->position.x = windowElements->WINDOW_WIDTH*2/3;

    std::vector<GameEntity*> enemyWaveVector(enemyWave, enemyWave + sizeof(enemyWave)/sizeof(GameEntity*));

    return enemyWaveVector;
}

std::vector<GameEntity*> GameEntityFactory::createEnemyWaveStraight3()
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

GameEntity* GameEntityFactory::createExplosion(GameEntity* destroyedEntity)
{
    GameEntity* explosion = new GameEntity();
    explosion->addRenderComponent(new ExplosionRenderComponent(explosion, windowElements, destroyedEntity));
    explosion->addPhysicsComponent(new ExplosionPhysicsComponent(explosion, windowElements));
    gameEntityManager->addEffectEntity(explosion);

    return explosion;
}

GameEntity* GameEntityFactory::createPlayer()
{
    GameEntity* player = new GameEntity();
    player->addRenderComponent(new PlayerRenderComponent(player, windowElements));
    player->addPhysicsComponent(new PlayerPhysicsComponent(player, windowElements, this));
    player->addCollisionComponent(new PlayerCollisionComponent(player, windowElements, gameEntityManager->getCollisionManager()));
    player->addInputComponent(new PlayerInputComponent(player, windowElements));
    gameEntityManager->addPhysicalEntity(player);

    return player;
}

GameEntity* GameEntityFactory::createPlayerProjectile(GameEntity* playerEntity)
{
    GameEntity* projectile = new GameEntity();
    projectile->addRenderComponent(new PlayerProjectileRenderComponent(projectile, windowElements, playerEntity));
    projectile->addPhysicsComponent(new PlayerProjectilePhysicsComponent(projectile, windowElements));
    projectile->addCollisionComponent(new PlayerProjectileCollisionComponent(projectile, windowElements, gameEntityManager->getCollisionManager()));
    gameEntityManager->addPhysicalEntity(projectile);

    return projectile;
}

GameEntity* GameEntityFactory::createPlayerInstructions()
{
    GameEntity* player = new GameEntity();
    PlayerRenderComponent* playerRender = new PlayerRenderComponent(player, windowElements);
    playerRender->getTexture()->enableAlphaBlend();
    player->addRenderComponent(playerRender);
    player->addPhysicsComponent(new PlayerInstructionsPhysicsComponent(player, windowElements, this));
    player->addInputComponent(new PlayerInstructionsInputComponent(player, windowElements));
    gameEntityManager->addPhysicalEntity(player);

    return player;
}

GameEntity* GameEntityFactory::createPlayerInstructionsProjectile(GameEntity* playerEntity)
{
    GameEntity* projectile = new GameEntity();
    projectile->addRenderComponent(new PlayerProjectileRenderComponent(projectile, windowElements, playerEntity));
    projectile->addPhysicsComponent(new PlayerInstructionsProjectilePhysicsComponent(projectile, windowElements));
    projectile->addCollisionComponent(new PlayerProjectileCollisionComponent(projectile, windowElements, gameEntityManager->getCollisionManager()));
    gameEntityManager->addPhysicalEntity(projectile);

    return projectile;
}

GameEntity* GameEntityFactory::createMeteor()
{
    GameEntity* meteor = new GameEntity();
    meteor->addRenderComponent(new MeteorRenderComponent(meteor, windowElements));
    meteor->addPhysicsComponent(new MeteorPhysicsComponent(meteor, windowElements));
    gameEntityManager->addPhysicalEntity(meteor);

    return meteor;
}
