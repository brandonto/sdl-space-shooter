/*******************************************************************//*
 * This class encapsulates functionality functionality for textures
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2015-02-05
 * @modified    2015-02-05
 *********************************************************************/
#ifndef SPACESHOOTER_TEXTURE_
    #define SPACESHOOTER_TEXTURE_

#include <SDL2/SDL.h>
#include <vector>

#define OPAQUE 255

class Texture
{
    private:
        //Fields
        SDL_Texture* sprite;
        SDL_Rect renderRect;
        int spriteWidth;
        int spriteHeight;

        double angle;

        int alpha;
        bool alphaEnabled;

        std::vector<SDL_Rect> animationRect;
        int currentAnimationFrame;
        bool partitioned;

    public:
        //Constructor
        Texture();

        //Destructor
        ~Texture();

        //Methods
        void setTexture(std::string imagePath);
        void setRenderRect(SDL_Rect* rect);
        SDL_Rect getRenderRect();
        void setRenderRect(SDL_Rect* rect);
        int getSpriteWidth();
        int getSpriteHeight();

        void setAngle();
        double getAngle();

        void enableAlphaBlend();
        void disableAlphaBlend();
        void setAlphaBlend(Uint8 alpha);
        Uint8 getAlphaBlend();

        bool partitionSpritesheet(std::string xmlPath);
        bool advanceAnimation()
        bool setAnimationFrame(int animationFrame)
};

#endif
