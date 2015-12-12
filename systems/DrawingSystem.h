#ifndef H_DRAWING_SYSTEM
#define H_DRAWING_SYSTEM

#include "../components/DrawableComponent.h"
#include "System.h"

namespace zen
{
    class DrawingSystem : public System
    {
    public:
        DrawingSystem(sf::RenderTarget* target);

        virtual void run(Entity* entity, float time) override;
    private:
        sf::RenderTarget* target;
    };
}
#endif
