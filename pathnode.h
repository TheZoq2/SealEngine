#ifndef H_PATHNODE
#define H_PATHNODE

#include "vec2f.h"

namespace zen
{

    class Platform;

    class PathNode
    {
    public:
        enum LinkType
        {
            LOCAL,
            JUMP
        };
        struct Link
        {
            Link(LinkType type, PathNode* otherNode, float jumpPower)
            {
                this->type = type;
                this->otherNode = otherNode;
                this->jumpPower = jumpPower;
            }
            Link(LinkType type, PathNode* otherNode)
                : Link(type, otherNode, 0)
            {
            }
            LinkType type;
            PathNode* otherNode;

            float jumpPower;
        };

        PathNode(Vec2f position, Platform* parent);

        void addLink(PathNode* other, LinkType type);

        Vec2f getPosition();
        Platform* getPlatform();
        std::vector<Link> getLinks();
    private:
        Vec2f position;

        std::vector<Link> links;

        Platform* platform;
    };

}
#endif
