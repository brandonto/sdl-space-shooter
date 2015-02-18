/*******************************************************************//*
 * Interface implementing the Observer pattern
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2015-02-12
 * @modified    2015-02-17
 *********************************************************************/
#ifndef SPACESHOOTER_IOBSERVER_H_
    #define SPACESHOOTER_IOBSERVER_H_

#include <algorithm> //std::find
#include <list>
#include <string>
#include "GameEntity.h"

class IObserver
{
    private:

    public:
        //Destructor
        virtual ~IObserver(){};

        //Methods
        virtual void onNotify(GameEntity* entity, int event) = 0;
};

class IObservable
{
    private:
        std::list<IObserver*> observers;

    public:
        //Destructor
        virtual ~IObservable(){};

        //Methods
        virtual void addObserver(IObserver* obs)
        {
            observers.push_back(obs);
        }

        virtual void removeObserver(IObserver* obs)
        {
            observers.erase(std::find(observers.begin(), observers.end(), obs));
        }

    protected:
        virtual void notify(GameEntity* entity, int event)
        {
            std::list<IObserver*>::iterator iterator;
            for (   iterator=observers.begin();
                    iterator!=observers.end();
                    iterator++)
            {
                (*iterator)->onNotify(entity, event);
            }
        };
};

#endif

