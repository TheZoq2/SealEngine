#include "System.h"

using namespace zen;

System::System()
{
}

void System::setOwner(EntityGroup* owner) 
{
    this->owner = owner;
}
