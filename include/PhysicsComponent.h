/*******************************************************************//*
 * Interface containing one method that all physics components must
 * implement
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2014-09-06
 * @modified    2015-02-17
 *********************************************************************/
#ifndef SPACESHOOTER_PHYSICSCOMPONENT_
    #define SPACESHOOTER_PHYSICSCOMPONENT_

class GameEntity;

struct WindowElements;

class PhysicsComponent
{
    protected:
        int health = 1;
        int maxHealth = 1;

    public:
        GameEntity* gameEntity;
        WindowElements* windowElements;

        //Destructor
        virtual ~PhysicsComponent(){};

        //Methods
        virtual void update() = 0;
        virtual void pauseTimers(){};
        virtual void resumeTimers(){};

        virtual void onHit(){};
        virtual void onDestroy(){};

        int getHealth(){ return health; };
        int getMaxHealth(){ return maxHealth; };
        void setMaxHealth(int hp){ maxHealth=hp; health=hp; };
        bool decrementHealth(int val)
        {
            health-=val;
            if (health <= 0)
            {
                return false;
            }
            return true;
        };
        void incrementHealth(int val)
        {
            health+=val;
            if (health > maxHealth)
            {
                health = maxHealth;
            }
        };
};

#endif
