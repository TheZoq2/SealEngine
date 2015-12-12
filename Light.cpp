#include "Light.h"

using namespace zen;

Light::Light(Vec2f position, sf::Color color, float range) 
{
    this->position = position;
    this->color = color;
    this->range = range;

    std::cout << range << std::endl;
}

void Light::setPosition(Vec2f position)
{
    this->position = position;
}

Vec2f Light::getPosition()
{
    return position;
}
sf::Color Light::getColor()
{
    return color;
}
float Light::getRange()
{
    return range;
}
