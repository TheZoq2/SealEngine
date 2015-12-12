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

int LightManager::lightAmount()
{
    return lights.size();
}

