/*******************************************************************//*
 * Implementation of the UIScoreRenderComponent class.
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2015-02-18
 * @modified    2015-02-19
 *********************************************************************/
#include "UIScoreRenderComponent.h"

#include <cstddef>

#include "GameEntity.h"
#include "Texture.h"
#include "Util.h"
#include "WindowElements.h"

UIScoreRenderComponent::UIScoreRenderComponent(GameEntity* gameEntity,
                                               WindowElements* windowElements)
:   scorePointer(NULL)
{
    this->gameEntity = gameEntity;
    this->windowElements = windowElements;

    texture = NULL;

    numScoreTextures[0] = new Texture(windowElements);
    numScoreTextures[0]->setTexture(Util::fix_path("../data/graphics/ui/numeral0.png"));

    numScoreTextures[1] = new Texture(windowElements);
    numScoreTextures[1]->setTexture(Util::fix_path("../data/graphics/ui/numeral1.png"));

    numScoreTextures[2] = new Texture(windowElements);
    numScoreTextures[2]->setTexture(Util::fix_path("../data/graphics/ui/numeral2.png"));

    numScoreTextures[3] = new Texture(windowElements);
    numScoreTextures[3]->setTexture(Util::fix_path("../data/graphics/ui/numeral3.png"));

    numScoreTextures[4] = new Texture(windowElements);
    numScoreTextures[4]->setTexture(Util::fix_path("../data/graphics/ui/numeral4.png"));

    numScoreTextures[5] = new Texture(windowElements);
    numScoreTextures[5]->setTexture(Util::fix_path("../data/graphics/ui/numeral5.png"));

    numScoreTextures[6] = new Texture(windowElements);
    numScoreTextures[6]->setTexture(Util::fix_path("../data/graphics/ui/numeral6.png"));

    numScoreTextures[7] = new Texture(windowElements);
    numScoreTextures[7]->setTexture(Util::fix_path("../data/graphics/ui/numeral7.png"));

    numScoreTextures[8] = new Texture(windowElements);
    numScoreTextures[8]->setTexture(Util::fix_path("../data/graphics/ui/numeral8.png"));

    numScoreTextures[9] = new Texture(windowElements);
    numScoreTextures[9]->setTexture(Util::fix_path("../data/graphics/ui/numeral9.png"));

    renderRect.x = 20;
    renderRect.y = 20;
    renderRect.w = 10;
    renderRect.h = 10;

}

void UIScoreRenderComponent::update()
{
    numScoreRect[0].x = renderRect.x;
    numScoreRect[0].y = renderRect.y;
    numScoreRect[0].w = renderRect.w/SCORE_DIGITS;
    numScoreRect[0].h = renderRect.h;
    for (int i=1; i<SCORE_DIGITS; i++)
    {
        numScoreRect[i].x = numScoreRect[0].x + i*numScoreRect[0].w;
        numScoreRect[i].y = numScoreRect[0].y;
        numScoreRect[i].w = numScoreRect[0].w;
        numScoreRect[i].h = numScoreRect[0].h;
    }

    if (scorePointer!=NULL)
    {
        for (int i=0; i<SCORE_DIGITS; i++)
        {
            SDL_RenderCopy(windowElements->renderer, numScoreTextures[((*scorePointer)/pow(10,SCORE_DIGITS-i-1))%10]->getTexture(), NULL, &numScoreRect[i]);
        }
    }
    else
    {
        for (int i=0; i<SCORE_DIGITS; i++)
        {
            SDL_RenderCopy(windowElements->renderer, numScoreTextures[0]->getTexture(), NULL, &numScoreRect[i]);
        }
    }
}

// Enables alpha blending effect on texture
void UIScoreRenderComponent::enableBlending()
{
    texture->enableAlphaBlend();
}

// Sets the alpha value of the texture
void UIScoreRenderComponent::setAlphaBlend(Uint8 alpha)
{
    texture->setAlphaBlend(alpha);
}

// Returns the alpha value of the texture
Uint8 UIScoreRenderComponent::getAlphaBlend()
{
    return texture->getAlphaBlend();
}

void UIScoreRenderComponent::setScorePointer(int* ptr)
{
    scorePointer = ptr;
}

UIScoreRenderComponent::~UIScoreRenderComponent()
{
    if (texture!=NULL) { delete texture; }
    std::map<int, Texture*>::iterator textureIterator;
    for (   textureIterator=numScoreTextures.begin();
            textureIterator!=numScoreTextures.end();
            textureIterator++)
    {
        delete (*textureIterator).second;
    }
}

int UIScoreRenderComponent::pow(int base, int exp)
{
    if (exp == 0)
    {
        return 1;
    }
    if (exp == 1)
    {
        return base;
    }

    int tmp = pow(base, exp/2);

    if (exp%2 == 0)
    {
        return tmp * tmp;
    }
    else
    {
        return base * tmp * tmp;
    }
}
