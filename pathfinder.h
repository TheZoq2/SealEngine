#ifndef H_PATHFINDER
#define H_PATHFINDER

#include <list>

#include "entitygroup.h"
#include "pathnode.h"

namespace zen
{
    class Pathfinder
    {
    public:
        Pathfinder(EntityGroup* group);
    private:
        static const float MAX_NODE_DISTANCE;
        void generateLinks();

        EntityGroup* entityGroup;

        std::vector<PathNode*> nodes;
    };
}
#endif
