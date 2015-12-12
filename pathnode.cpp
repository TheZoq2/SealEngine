#include "pathnode.h"

using namespace zen;

PathNode::PathNode(Vec2f position, Platform* platform)
{
    this->position = position;
    this->platform = platform;
}

void PathNode::addLink(PathNode* other, LinkType type)
{
    links.push_back(Link(type, other));
}

Vec2f PathNode::getPosition()
{
    return this->position;
}
Platform* PathNode::getPlatform()
{
    return platform;
}
std::vector<PathNode::Link> PathNode::getLinks()
{
    return links;
}
