#include "DrawingSystem.h"

using namespace zen;

DrawingSystem::DrawingSystem(sf::RenderTarget* target)
    : System()
{
    this->target = target;
}

void DrawingSystem::run(zen::Entity* entity, float time)
{
    //DrawableComponent* drawable = entity->getComponent<DrawableComponent>();
    std::vector<DrawableComponent*> drawables = entity->getComponents<DrawableComponent>();

    for(auto& drawable : drawables)
    {
        drawable->draw(target);
    }
}

