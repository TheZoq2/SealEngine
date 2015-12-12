#include "TransformComponent.h"
#include "../entity.h"

using namespace zen;

void TransformComponent::setPosition(Vec2f position)
{
    this->position = position;

    //Transmit this change to the entity
    owner->handleComponentMessage<TransformComponent>(this, Messages::POSITION_CHANGED);
}
void TransformComponent::setPosition(float x, float y)
{
    setPosition(Vec2f(x, y));
}

void TransformComponent::setScale(Vec2f scale)
{
    this->scale = scale;
    //Transmit this change to the entity
    owner->handleComponentMessage<TransformComponent>(this, Messages::SCALE_CHANGED);
}
void TransformComponent::setScale(float x, float y)
{
    setScale(Vec2f(x, y));
}
void TransformComponent::setAngle(float angle)
{
    this->angle = angle;
    //Transmit this change to the entity
    owner->handleComponentMessage<TransformComponent>(this, Messages::ANGLE_CHANGED);
}

Vec2f TransformComponent::getPosition()
{
    return position;
}
Vec2f TransformComponent::getScale()
{
    return scale;
}
float TransformComponent::getAngle()
{
    return angle;
}
