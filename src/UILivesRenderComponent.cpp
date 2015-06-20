/*******************************************************************//*
 * Implementation of the UILivesRenderComponent class.
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2015-02-17
 * @modified    2015-02-18
 *********************************************************************/
#include "UILivesRenderComponent.h"

#include <cstddef>

#include "GameEntity.h"
#include "Texture.h"
#include "Util.h"
#include "WindowElements.h"
#include <algorithm>

UILivesRenderComponent::UILivesRenderComponent(GameEntity* gameEntity,
                                               WindowElements* windowElements)
:   livesPointer(NULL)
{
    this->gameEntity = gameEntity;
    this->windowElements = windowElements;

    texture = new Texture(windowElements);
    texture->setTexture(Util::fix_path("../data/graphics/ui/playerLife1_blue.png"));

    xTexture = new Texture(windowElements);
    xTexture->setTexture(Util::fix_path("../data/graphics/ui/numeralX.png"));

    numLivesTextures[0] = new Texture(windowElements);
    numLivesTextures[0]->setTexture(Util::fix_path("../data/graphics/ui/numeral0.png"));

    numLivesTextures[1] = new Texture(windowElements);
    numLivesTextures[1]->setTexture(Util::fix_path("../data/graphics/ui/numeral1.png"));

    numLivesTextures[2] = new Texture(windowElements);
    numLivesTextures[2]->setTexture(Util::fix_path("../data/graphics/ui/numeral2.png"));

    numLivesTextures[3] = new Texture(windowElements);
    numLivesTextures[3]->setTexture(Util::fix_path("../data/graphics/ui/numeral3.png"));

    numLivesTextures[4] = new Texture(windowElements);
    numLivesTextures[4]->setTexture(Util::fix_path("../data/graphics/ui/numeral4.png"));

    renderRect.x = 20;
    renderRect.y = 20;
    renderRect.w = 10;
    renderRect.h = 10;

}

void UILivesRenderComponent::update()
{
    xRect.x = renderRect.x + 1.2*renderRect.w;
    xRect.y = renderRect.y + 0.2*renderRect.h;
    xRect.w = renderRect.w - 0.4*renderRect.h;
    xRect.h = renderRect.h - 0.4*renderRect.h;

    numLivesRect.x = xRect.x + 1.2*xRect.w;
    numLivesRect.y = renderRect.y;
    numLivesRect.w = renderRect.w;
    numLivesRect.h = renderRect.h;

    SDL_RenderCopy(windowElements->renderer, texture->getTexture(), NULL, &renderRect);
    SDL_RenderCopy(windowElements->renderer, xTexture->getTexture(), NULL, &xRect);
    SDL_RenderCopy(windowElements->renderer, numLivesTextures[std::max(0, *livesPointer)]->getTexture(), NULL, &numLivesRect);
}

// Enables alpha blending effect on texture
void UILivesRenderComponent::enableBlending()
{
    texture->enableAlphaBlend();
}

// Sets the alpha value of the texture
void UILivesRenderComponent::setAlphaBlend(Uint8 alpha)
{
    texture->setAlphaBlend(alpha);
}

// Returns the alpha value of the texture
Uint8 UILivesRenderComponent::getAlphaBlend()
{
    return texture->getAlphaBlend();
}

void UILivesRenderComponent::setLivesPointer(int* ptr)
{
    livesPointer = ptr;
}

UILivesRenderComponent::~UILivesRenderComponent()
{
    if (texture!=NULL) { delete texture; }
    delete xTexture;
    std::map<int, Texture*>::iterator textureIterator;
    for (   textureIterator=numLivesTextures.begin();
            textureIterator!=numLivesTextures.end();
            textureIterator++)
    {
        delete (*textureIterator).second;
    }
}

