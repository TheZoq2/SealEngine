#include "LightManager.h"

using namespace zen;

int LightManager::addLight(Light* light)
{
    listHasChanged = true;

    return lights.push_back(light);
}

void LightManager::forgetLight(int id) 
{
    listHasChanged = true;

    lights.forget(id);
}

std::size_t LightManager::lightAmount()
{
    return lights.size();
}

std::vector<Light*> LightManager::getLightVector()
{
    tryRegenerateLists();
    return lightVector;
}

std::vector<float> LightManager::getRanges()
{
    tryRegenerateLists();
    return ranges;
}
std::vector<sf::Color> LightManager::getColors()
{
    tryRegenerateLists();
    return colors;
}
std::vector<Vec2f> LightManager::getPositions()
{
    tryRegenerateLists();
    return positions;
}

///////////////////////////////////////////////////////////////////////////////////
//                          Private members
///////////////////////////////////////////////////////////////////////////////////
void LightManager::tryRegenerateLists() 
{
    if(listHasChanged)
    {
        lightVector.clear();
        ranges.clear();
        colors.clear();
        positions.clear();

        for(auto light : lights.getElements())
        {
            lightVector.push_back(light);
            ranges.push_back(light->getRange());
            colors.push_back(light->getColor());
            positions.push_back(light->getPosition());

        }
    }
}
