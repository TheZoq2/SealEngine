#include "Component.h"

#include "../entity.h"

using namespace zen;

void Component::setOwner(Entity* owner) 
{
    this->owner = owner;

    //Notify all other components of this new change
    owner->handleComponentMessage(this, MessageTypes::ADDED);
}
