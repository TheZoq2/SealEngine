#include "platform.h"

//#define DEBUG_DRAW
using namespace zen;

const float Platform::PATH_NODE_DISTANCE = 50;

void Platform::create(Vec2f pos)
{
    this->pos = pos;
}
void Platform::draw(sf::RenderTarget* window)
{
    for(auto it : lines)
    {
        it.draw(window);
    }

#ifdef DEBUG_DRAW
    sf::CircleShape nodeShape(10);
    nodeShape.setFillColor(sf::Color(0,0,0,0));
    nodeShape.setOutlineColor(sf::Color(255,255,255,255));;

    nodeShape.setOutlineThickness(2);
    nodeShape.setOrigin(10,10);

    //std::cout << "new drawing" << std::endl;
    for(auto it : pathNodes)
    {
        //Debug drawing links
        for(auto link : it.getLinks())
        {
            if(link.type == PathNode::LinkType::JUMP)
            {
                sf::Vertex line[] = {
                    sf::Vertex(it.getPosition()),
                    sf::Vertex(link.otherNode->getPosition())
                };
                
                window->draw(line, 2, sf::LinesStrip);
            }
        }
       

        nodeShape.setPosition(it.getPosition());
        window->draw(nodeShape);
    }
#endif
}

void Platform::addPoint(Vec2f point)
{
    std::vector<Vec2f>::iterator insertPos = points.end();
    //Checking where the point should go
    for(std::vector<Vec2f>::iterator it = points.begin(); it != points.end(); it++)
    {
        if(point.x < it->x)
        {
            insertPos = it;
            break;
        }
    }

    points.insert(insertPos, point);

    generateLines();
}
void Platform::addPoint(float x, float y)
{
    addPoint(Vec2f(x, y));
}

Line::IntersectResult Platform::getCollision(Line* otherLine)
{
    Line::IntersectResult intersect;
    intersect.intersected = false;

    //Going through all the lines to check for collision
    for(auto it : lines)
    {
        intersect = it.getIntersect(otherLine);
        if(intersect.intersected == true)
        {
            return intersect;
        }
    }
    
    return intersect;
}
float Platform::getLocalX(float globalX)
{
    return globalX - pos.x;
}
bool Platform::xIsOnPlatform(float localX)
{
    return localX >= points.front().x && localX <= points.back().x;
}
Vec2f Platform::getGlobalPos(float localX)
{
    Vec2f result(0,0);

    float globalX = localX + pos.x;

    //Make sure the pos is actually on the platform
    if(xIsOnPlatform(localX) == false)
    {
        fprintf(stderr, "Local x coordinate is not on platform in Platform::getGlobalPos()\n");
    }

    //Loop through the lines to find the correct position
    for(auto it : lines)
    {
        if(globalX >= it.getPosition(0).x && globalX <= it.getPosition(1).x)
        {
            result.x = globalX;
            result.y = it.calculateYValue(globalX);
        }
    }
    
    return result;
}

void Platform::setPosition(Vec2f pos)
{
    this->pos = pos;

    generateLines();
}

std::vector<PathNode>* Platform::getPathNodes()
{
    return &pathNodes;
}

//////////////////////////////////////////////////////////////////////////////
//  Private methods
//////////////////////////////////////////////////////////////////////////////

void Platform::generateLines()
{
    lines.clear();

    //If there is only one point, a line can't be generated
    if(points.size() <= 1)
    {
        return;
    }

    for(unsigned int i = 0; i < points.size() - 1; i++)
    {
        lines.push_back(Line(points.at(i) + pos, points.at(i + 1) + pos));
    }
}

void Platform::generatePathNodes()
{
    //Create path nodes that are adequetly placed along the platform
    for(float nodePos = points[0].x; nodePos < points.back().x; nodePos += PATH_NODE_DISTANCE)
    {
        pathNodes.push_back(PathNode(getGlobalPos(nodePos), this));
    }
    //Put one node on the edge of the platform which might not be reached otherwise
    pathNodes.push_back(PathNode(getGlobalPos(points.back().x), this));

    //Linking the nodes on the same platform together
    for(auto it = pathNodes.begin() + 0; it != pathNodes.end(); ++it)
    {
        if(it != pathNodes.begin())
        {
            it->addLink(&*(it-1), PathNode::LOCAL);
        }
        if(it != pathNodes.end() - 1)
        {
            it->addLink(&*(it-1), PathNode::LOCAL);
        }
    }
}
