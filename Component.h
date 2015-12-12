#ifndef H_COMPONENT
#define H_COMPONENT

#include "../vec2f.h"

namespace zen
{
    class Entity;

    class Component
    {
    public:
        enum MessageTypes
        {
            ADDED = -1
        };

        //TODO Add virtual destructor
        //virtual ~Component() = 0;
        
        virtual void setOwner(Entity* owner);

        virtual void receiveComponentMessage(Component* other, int message){};

    protected:
        Entity* owner;
    private:
    };
}

#endif
