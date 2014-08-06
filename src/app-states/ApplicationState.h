#ifndef _APPLICATIONSTATE_H_
    #define _APPLICATIONSTATE_H_

/*******************************************************************//*
 * Abstract application state class. ApplicationState subclasses must
 * override the pure virtual methods to satisfy the main game loop
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2014-08-05
 * @modified    2014-08-06
 *********************************************************************/

class ApplicationState
{
    public:
        //Destructor
        virtual ~ApplicationState();

        //Methods
        virtual void onEnter();
        virtual void onEvent() = 0;
        virtual void onLoop() = 0;
        virtual void onRender() = 0;
        virtual void onExit();
};


/*******************************************************************//*
 * Enumerations for various states
 *********************************************************************/

enum ApplicationStates
{
    STATE_NULL,
    STATE_INTRO,
    STATE_MENU,
    STATE_GAME,
    STATE_PAUSE,
    STATE_GAMEOVER,
    STATE_OPTIONS,
    STATE_INSTRUCTIONS,
    STATE_HIGHSCORES,
    STATE_QUIT,
    STATE_CREDITS,
};

#endif
