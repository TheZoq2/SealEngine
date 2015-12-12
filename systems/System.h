#ifndef H_SYSTEM
#define H_SYSTEM

#include "../entitygroup.h"

namespace zen
{
    class Entity;
    class EntityGroup;

    class System
    {
    public:
        System();

        virtual void run(Entity* entity, float time) = 0;

        virtual void setOwner(EntityGroup* owner);
    protected:
        EntityGroup* owner;
    };
}
#endif
