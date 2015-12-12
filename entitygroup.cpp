#include "entitygroup.h"

using namespace zen;

EntityGroup::EntityGroup()
{
    nextPlatformID = 0;
}
void EntityGroup::addEntity(Entity* entity)
{
    entity->setGroup(this);
    this->insertEntity(entity);
}
int EntityGroup::addPlatform(Platform* platform)
{

    IDPlatform newPlatform;
    newPlatform.id = nextPlatformID;
    newPlatform.platform = platform;

    this->platforms.push_back(newPlatform);

    nextPlatformID++;

    return nextPlatformID - 1; //TODO: Possibly thange to nextPlatform++
}

void EntityGroup::insertEntity(Entity* entity)
{
    //Go through the entities and find where to put the new entity
    for(auto it = entities.begin(); it != entities.end(); it++)
    {
        //Check if the depth is correct
        if(it->get()->getDepth() > entity->getDepth())
        {
            entities.insert(it, std::unique_ptr<Entity>(entity));
            //We found the correct location which means we are done. Return to avoid weird issues.
            return;
        }
    }
    
    //The entity should be added in the back because it has the lowest depth yet
    entities.push_back(std::unique_ptr<Entity>(entity));
}

void EntityGroup::onEntityDepthChange(Entity* entity)
{
    std::vector< std::unique_ptr<Entity> >::iterator it;
    //Remove the entity from the list
    for(it = entities.begin(); it != entities.end(); it++)
    {
        //If this is the element we are looking for
        if(it->get() == entity)
        {
            entities.erase(it);
            break; //Avoid going further. Iterator is broken now
        }
    }

    //Insert the entity in the new position
    insertEntity(entity);
}

void EntityGroup::update(float frameTime)
{
    for(auto& it : entities)
    {
        it->update(frameTime);
    }
}
void EntityGroup::draw(sf::RenderTarget* target)
{
    for(auto& it : platforms)
    {
        it.platform->draw(target);
    }
}

std::vector<EntityGroup::IDPlatform> EntityGroup::getPlatforms()
{
    return platforms;
}
bool EntityGroup::platformExists(uint32_t id)
{
    for(auto it : platforms)
    {
        if(it.id == id)
        {
            return true;
        }
    }
    return false;
}
Platform* EntityGroup::getPlatformByID(uint32_t id)
{
    for(auto it : platforms)
    {
        if(it.id == id)
        {
            return it.platform;
        }
    }
    return NULL;
}
LightManager* EntityGroup::getLightManager()
{
    return &lightManager;
}

EntityGroup::PlatformCollisionResult EntityGroup::getPlatformCollision(Vec2f originPos, Line* line)
{

    //Finding which platform, if any is hit first
    PlatformCollisionResult result;
    result.intResult.intersected = false;
    float lowestDist;
    for(auto it : platforms)
    {
        Line::IntersectResult intResult = it.platform->getCollision(line);
        
        if(intResult.intersected == true)
        {
            float intersectDist = ((Vec2f)(intResult.pos - originPos)).length();
            //If this is the first intersection
            if(result.intResult.intersected == false)
            {
                result.intResult = intResult;
                result.platformID = it.id;
                
                lowestDist = intersectDist;
            }
            else
            {
                if(intersectDist < lowestDist)
                {
                    lowestDist = intersectDist;
                    result.intResult = intResult;
                    result.platformID = it.id;
                }
            }
        }
    }

    return result;
}
