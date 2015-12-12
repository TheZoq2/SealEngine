#include "pathfinder.h"

const float zen::Pathfinder::MAX_NODE_DISTANCE = 400;

zen::Pathfinder::Pathfinder(EntityGroup* group)
{
    this->entityGroup = group;

    generateLinks();
}

/////////////////////////////////////////////////////////////////////
//                      Private methods
/////////////////////////////////////////////////////////////////////

void zen::Pathfinder::generateLinks()
{
    nodes.clear();

    //Go through the all the platforms in the entity group
    std::vector<EntityGroup::IDPlatform> platforms = entityGroup->getPlatforms();
    for(auto it : platforms)
    {
        it.platform->generatePathNodes();
        std::vector<PathNode>* pathNodes = it.platform->getPathNodes();
        //Iterate over the path nodes in that platform
        for(auto node = pathNodes->begin(); node != pathNodes->end(); ++node)
        {
            //Add the pointer to the node to the list of nodes
            nodes.push_back(&*node);
        }
    }

    //Iterate over all the nodes in the list
    for(auto it = nodes.begin(); it != nodes.end(); ++it)
    {
        //Iterate over the rest of the nodes to check them against it
        for(auto node = it; node != nodes.end(); ++node)
        {
            //Checking if they are on the different platform
            if((*node)->getPlatform() != (*it)->getPlatform())
            {
                float distance = static_cast<Vec2f>((*node)->getPosition() - (*it)->getPosition()).length();

                if(distance < MAX_NODE_DISTANCE)
                {
                   (*node)->addLink(*it, PathNode::JUMP); 
                   (*it)->addLink(*node, PathNode::JUMP); 
                }
            }
        }
    }
}

