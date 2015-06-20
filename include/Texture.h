/*******************************************************************//*
 * This class encapsulates functionality functionality for textures
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2015-02-05
 * @modified    2015-02-19
 *********************************************************************/
#ifndef SPACESHOOTER_TEXTURE_
    #define SPACESHOOTER_TEXTURE_

#include <string>
#include <vector>

#ifdef _WIN32
	#include <SDL.h>
#endif

#ifdef __linux
	#include <SDL2/SDL.h>
#endif

#define OPAQUE 255

struct WindowElements;

class Texture
{
    private:
        //Fields
        WindowElements* windowElements;
        SDL_Texture* sprite;
        SDL_Rect sourceRect;
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
        Texture(WindowElements* windowElements);

        //Destructor
        ~Texture();

        //Methods
        void setTexture(std::string imagePath);
        void setTexture(SDL_Texture* texture);
        SDL_Texture* getTexture();
        void setSourceRect(SDL_Rect* rect);
        SDL_Rect getSourceRect();
        int getSpriteWidth();
        int getSpriteHeight();

        void setAngle(double angle);
        double getAngle();

        void enableAlphaBlend();
        void disableAlphaBlend();
        void setAlphaBlend(Uint8 alpha);
        Uint8 getAlphaBlend();

        bool partitionSpritesheet(std::string xmlPath);
        bool advanceAnimation();
        bool setAnimationFrame(int animationFrame);
};

#endif
