/*******************************************************************//*
 * The core component bag class for the component-entity system used in
 * throughout this game. Doesn't do anything useful apart from holding
 * references to the various components
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2014-08-10
 * @modified    2014-08-20
 *********************************************************************/
#ifndef SPACESHOOTER_GAMEENTITY_H_
    #define SPACESHOOTER_GAMEENTITY_H_

//class InputComponent;
class RenderComponent;
//#include "RenderComponent.h"

class GameEntity
{
    private:
        //Fields
        //InputComponent* input;
        RenderComponent* render;

    public:
        //Fields
        int xPos, yPos;
        int velocity;

        //Constructor
        GameEntity( RenderComponent* render
                  );

        //Methods
        void onEvent();
        void onUpdate();
        void onRender();
};

#endif
