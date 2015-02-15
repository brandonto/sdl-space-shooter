/*******************************************************************//*
 * Implementation of the GameEntityFactory class.
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2015-02-07
 * @modified    2015-02-14
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
    stringToEntityEnum["enemyStraight"] = ENTITY_ENEMYSTRAIGHT;
    stringToEntityEnum["enemyZigZag"] = ENTITY_ENEMYZIGZAG;
    stringToEntityEnum["player"] = ENTITY_PLAYER;
    stringToEntityEnum["sprite"] = ENTITY_SPRITE;
    stringToEntityEnum["text"] = ENTITY_TEXT;
    stringToEntityEnum["uiPanel"] = ENTITY_UIPANEL;
}

GameEntityFactory::~GameEntityFactory()
{

}

std::vector<GameEntity*> GameEntityFactory::createBackgroundEntities()
{
    std::vector<EntityXmlStruct> xmlStructs = gameEntityData.getBackgroundData(gameEntityManager->getState());
    GameEntity* background[1];
    background[0] = createBackground();
    std::vector<GameEntity*> backgroundVector(background, background + sizeof(background)/sizeof(GameEntity*));
    return backgroundVector;
}

std::vector<GameEntity*> GameEntityFactory::createPhysicalEntities()
{
    std::vector<EntityXmlStruct> xmlStructs = gameEntityData.getPhysicalData(gameEntityManager->getState());
    int numEntities = xmlStructs.size();

    GameEntity* physical[numEntities];

    for (int i=0; i<numEntities; i++)
    {
        physical[i] = createEntity(xmlStructs[i]);
    }

    std::vector<GameEntity*> physicalVector(physical, physical + sizeof(physical)/sizeof(GameEntity*));
    return physicalVector;
}

std::vector<GameEntity*> GameEntityFactory::createEffectEntities()
{
    //gameEntityData.getEffectData(gameEntityManager->getState());
}

std::vector<GameEntity*> GameEntityFactory::createUIEntities()
{
    std::vector<EntityXmlStruct> xmlStructs = gameEntityData.getUIData(gameEntityManager->getState());
    int numEntities = xmlStructs.size();

    GameEntity* ui[numEntities];

    for (int i=0; i<numEntities; i++)
    {
        ui[i] = createEntity(xmlStructs[i]);
    }

    std::vector<GameEntity*> uiVector(ui, ui + sizeof(ui)/sizeof(GameEntity*));
    return uiVector;
}

GameEntity* GameEntityFactory::createEntity(std::string type)
{
    EntityXmlStruct xmlStruct = gameEntityData.getDataByType(gameEntityManager->getState(), type);
    return createEntity(xmlStruct);
}

GameEntity* GameEntityFactory::createEntity(SpawnData data)
{
    EntityXmlStruct xmlStruct = gameEntityData.getDataByType(gameEntityManager->getState(), data.type);
    xmlStruct.x = data.x;
    xmlStruct.y = data.y;
    return createEntity(xmlStruct);
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

        case ENTITY_ENEMYSTRAIGHT:
        {
            entity->addRenderComponent(new EnemyRenderComponent(entity, windowElements));
            entity->addPhysicsComponent(new EnemyPhysicsComponent(entity, windowElements, this));
            entity->addCollisionComponent(new EnemyCollisionComponent(entity, windowElements, gameEntityManager->getCollisionManager()));
            entity->position.x = xmlStruct.x;
            entity->position.y = xmlStruct.y;
            configureEntity(entity, xmlStruct);
            gameEntityManager->addPhysicalEntity(entity);
            break;
        }

        case ENTITY_PLAYER:
        {
            entity->addRenderComponent(new PlayerRenderComponent(entity, windowElements));
            entity->addPhysicsComponent(new PlayerPhysicsComponent(entity, windowElements, this));
            entity->addCollisionComponent(new PlayerCollisionComponent(entity, windowElements, gameEntityManager->getCollisionManager()));
            entity->addInputComponent(new PlayerInputComponent(entity, windowElements));
            entity->position.x = xmlStruct.x;
            entity->position.y = xmlStruct.y;
            configureEntity(entity, xmlStruct);
            gameEntityManager->addPhysicalEntity(entity);
            break;
        }

        case ENTITY_SPRITE:
        {
            entity->addRenderComponent(new SpriteRenderComponent(entity, windowElements));
            SDL_Rect rect = entity->getRenderComponent()->getRenderRect();
            rect.x = xmlStruct.x;
            rect.y = xmlStruct.y;
            entity->getRenderComponent()->setRenderRect(&rect);
            configureEntity(entity, xmlStruct);
            gameEntityManager->addPhysicalEntity(entity);
            break;
        }

        case ENTITY_TEXT:
        {
            TextRenderComponent* entityRender = new TextRenderComponent(entity, windowElements);
            entityRender->setText(xmlStruct.data, 96);
            entity->addRenderComponent(entityRender);
            SDL_Rect rect = entity->getRenderComponent()->getRenderRect();
            rect.x = xmlStruct.x;
            rect.y = xmlStruct.y;
            entity->getRenderComponent()->setRenderRect(&rect);
            configureEntity(entity, xmlStruct);
            gameEntityManager->addUIEntity(entity);
            break;
        }

        case ENTITY_UIPANEL:
        {
            UIPanelRenderComponent* entityRender = new UIPanelRenderComponent(entity, windowElements);
            entity->addRenderComponent(entityRender);
            SDL_Rect rect = entity->getRenderComponent()->getRenderRect();
            rect.x = xmlStruct.x;
            rect.y = xmlStruct.y;
            entity->getRenderComponent()->setRenderRect(&rect);
            if (xmlStruct.function != "NONE")
            {
                UIPanelInputComponent* entityInput = new UIPanelInputComponent(entity);
                UIClickFunction* clickFunction = new UIClickFunction(gameEntityManager->getState());
                clickFunction->setCallback(xmlStruct.function);
                entityInput->addClickFunction(clickFunction);
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
    SDL_Rect rect = entity->getRenderComponent()->getRenderRect();
    rect.w = xmlStruct.width;
    rect.h = xmlStruct.height;
    entity->getRenderComponent()->setRenderRect(&rect);
    if (xmlStruct.alphaEnabled)
    {
        entity->getRenderComponent()->getTexture()->enableAlphaBlend();
    }
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

GameEntity* GameEntityFactory::createPlayerProjectile(GameEntity* playerEntity)
{
    GameEntity* projectile = new GameEntity();
    projectile->addRenderComponent(new PlayerProjectileRenderComponent(projectile, windowElements, playerEntity));
    projectile->addPhysicsComponent(new PlayerProjectilePhysicsComponent(projectile, windowElements));
    projectile->addCollisionComponent(new PlayerProjectileCollisionComponent(projectile, windowElements, gameEntityManager->getCollisionManager()));
    gameEntityManager->addPhysicalEntity(projectile);

    return projectile;
}

std::vector<GameEntity*> GameEntityFactory::createPlayerInstructions()
{
    GameEntity* player[1];
    player[0]= new GameEntity();
    PlayerRenderComponent* playerRender = new PlayerRenderComponent(player[0], windowElements);
    playerRender->getTexture()->enableAlphaBlend();
    player[0]->addRenderComponent(playerRender);
    player[0]->addPhysicsComponent(new PlayerInstructionsPhysicsComponent(player[0], windowElements, this));
    player[0]->addInputComponent(new PlayerInstructionsInputComponent(player[0], windowElements));
    gameEntityManager->addPhysicalEntity(player[0]);

    std::vector<GameEntity*> playerVector(player, player + sizeof(player)/sizeof(GameEntity*));
    return playerVector;
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
