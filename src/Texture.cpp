/*******************************************************************//*
 * Implementation of the Texture class.
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2015-02-05
 * @modified    2015-02-18
 *********************************************************************/
#include "Texture.h"

#include <cstddef>
#include <cstdio>

#include "SDL_util.h"
#include "tinyxml.h"
#include "WindowElements.h"

Texture::Texture(WindowElements* windowElements)
:   sprite(NULL),
    spriteWidth(0),
    spriteHeight(0),
    angle(0),
    alpha(OPAQUE),
    alphaEnabled(false),
    currentAnimationFrame(0),
    partitioned(false)
{
    this->windowElements = windowElements;
}

// Sets the sprite to the image given in imagePath
void Texture::setTexture(std::string imagePath)
{
    // Creates a new sprite from the filepath given in imagePath
    SDL_Texture* newSprite = SDL_util::create_texture_from_image(windowElements, imagePath);
    if (newSprite == NULL)
    {
        printf("[ERROR] setTexture(): Texture could not be constructed from image.\n");
    }

    // If there was a previously set sprite, destroy the sprite and reset variables
    if (sprite != NULL)
    {
        SDL_DestroyTexture(sprite);
        sprite = NULL;
        alpha = OPAQUE;
        alphaEnabled = false;
        currentAnimationFrame = 0;
        partitioned = false;
    }

    // Sets the current sprite to the newly created sprite
    sprite = newSprite;
    newSprite = NULL;

    // Sets spriteWidth and spriteHeight to the width and height of the new image
    SDL_QueryTexture(sprite, NULL, NULL, &spriteWidth, &spriteHeight);
    sourceRect.x = 0;
    sourceRect.y = 0;
    sourceRect.w = spriteWidth;
    sourceRect.h = spriteHeight;
}

// Sets the sprite to be the one passed in
void Texture::setTexture(SDL_Texture* texture)
{
    // If there was a previously set sprite, destroy the sprite and reset variables
    if (sprite != NULL)
    {
        SDL_DestroyTexture(sprite);
        sprite = NULL;
        alpha = OPAQUE;
        alphaEnabled = false;
        currentAnimationFrame = 0;
        partitioned = false;
    }

    sprite = texture;
    texture = NULL;

    // Sets spriteWidth and spriteHeight to the width and height of the new image
    SDL_QueryTexture(sprite, NULL, NULL, &spriteWidth, &spriteHeight);
    sourceRect.x = 0;
    sourceRect.y = 0;
    sourceRect.w = spriteWidth;
    sourceRect.h = spriteHeight;
}

// Getter for texture
SDL_Texture* Texture::getTexture()
{
    return sprite;
}

// Sets the area of the sprite that will be rendered
void Texture::setSourceRect(SDL_Rect* rect)
{
    sourceRect = *rect;
}

// Getter for sourceRect
SDL_Rect Texture::getSourceRect()
{
    return sourceRect;
}

// Getter for spriteWidth
int Texture::getSpriteWidth()
{
    return spriteWidth;
}

// Getter for spriteHeight
int Texture::getSpriteHeight()
{
    return spriteHeight;
}

// Sets the angle at which the sprite will be rendered
void Texture::setAngle(double angle)
{
    this->angle = angle;
}

// Getter for angle
double Texture::getAngle()
{
    return angle;
}

// Enables alpha blending. Must be called before setAlphaBlend()
void Texture::enableAlphaBlend()
{
    if (!alphaEnabled)
    {
        SDL_SetTextureBlendMode(sprite, SDL_BLENDMODE_BLEND);
        alphaEnabled = true;
    }
    else
    {
        printf("[WARNING] enableAlphaBlend(): Alpha blending is already enabled.\n");
    }
}

// Disables alpha blending.
void Texture::disableAlphaBlend()
{
    if (alphaEnabled)
    {
        SDL_SetTextureBlendMode(sprite, SDL_BLENDMODE_NONE);
        alphaEnabled = false;
    }
    else
    {
        printf("[WARNING] disableAlphaBlend(): Alpha blending is already disabled.\n");
    }
}

// Sets the alpha blend value that the texture will be rendered at.
// Must be called after enableAlphaBlend()
void Texture::setAlphaBlend(Uint8 alpha)
{
    if (alphaEnabled)
    {
        this->alpha = alpha;
        SDL_SetTextureAlphaMod(sprite, alpha);
    }
    else
    {
        printf("[ERROR] setAlphaBlend(): Alpha blending has not been enabled. Please call enableAlphaBlend() first.\n");
    }
}

// Returns the alpha value of the texture, should be called after enableAlphaBlend()
Uint8 Texture::getAlphaBlend()
{
    if (!alphaEnabled)
    {
        printf("[WARNING] getAlphaBlend(): Called before alpha blending has been enabled.\n");
    }
    return alpha;
}

// Creates an array of sub-textures for use in animation
bool Texture::partitionSpritesheet(std::string xmlPath)
{
    TiXmlDocument xmlDoc;

    // Return false if the XML file is not found
    if (!xmlDoc.LoadFile(xmlPath.c_str()))
    {
        printf("[ERROR] partitionSpritesheet(): Xml file not found.\n");
        return false;
    }

    // The root element of this xml file
    TiXmlElement* rootElement = xmlDoc.RootElement();

    // Parses through SubTexture elements to create partitioned SDL_Rects
    // and pushes onto vector
    for (   TiXmlElement* e = rootElement->FirstChildElement();
            e != NULL;
            e = e->NextSiblingElement())
    {
        SDL_Rect partitionedRect;
        partitionedRect.x = atoi(e->Attribute("x"));
        partitionedRect.y = atoi(e->Attribute("y"));
        partitionedRect.w = atoi(e->Attribute("width"));
        partitionedRect.h = atoi(e->Attribute("height"));
        animationRect.push_back(partitionedRect);
    }

    partitioned = true;
    currentAnimationFrame = 0;
    return true;
}

// Advances the animation by one frame
// Returns true if successful
// Returns false if texture is not partitioned or if no more animations
bool Texture::advanceAnimation()
{
    // Return immediately if texture is not partitioned
    if (!partitioned)
    {
        printf("[ERROR] advanceAnimation(): Texture is not partitioned.\n");
        return false;
    }

    // No more animations
    if (++currentAnimationFrame >= animationRect.size())
    {
        return false;
    }

    sourceRect = animationRect[currentAnimationFrame];
    return true;
}

// Sets the current animation frame
// Returns true if successful
// Returns false if texture is not partitioned or if animation frame is out of bounds
bool Texture::setAnimationFrame(int animationFrame)
{
    // Return immediately if texture is not partitioned
    if (!partitioned)
    {
        printf("[ERROR] setAnimationFrame(): Texture is not partitioned.\n");
        return false;
    }

    // Returns false if animation is out of bounds
    if (animationFrame<0 || animationRect.size()<animationFrame)
    {
        printf("[ERROR] setAnimationFrame(): Attempted to set to an invalid animation frame.\n");
        return false;
    }

    currentAnimationFrame = animationFrame;
    sourceRect = animationRect[animationFrame];
    return true;
}

Texture::~Texture()
{
    SDL_DestroyTexture(sprite);
    sprite = NULL;
}
