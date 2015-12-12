#include "world.h"

zen::World::World()
{
    gravity = 9.82;
}
zen::World::~World()
{
}

void zen::World::addEntityGroup(EntityGroup* group, float paralaxAmount)
{
    Layer layer; //The new layer to add;
    layer.eGroup = group;
    layer.paralaxAmount = paralaxAmount;

    layers.push_back(layer);
}

void zen::World::update(float frameTime)
{
    this->mainGroup.update(frameTime);

    for(auto it : this->layers)
    {
        it.eGroup->update(frameTime);
    }
}


float zen::World::getGravity()
{
    return gravity;
}
zen::EntityGroup* zen::World::getMainGroup()
{
    return &mainGroup;
}
