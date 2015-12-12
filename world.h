#ifndef H_WORLD
#define H_WORLD

#include <vector>
#include <stdint.h>
#include <iostream>

#include <SFML/Graphics.hpp>

#include "line.h"
#include "entity.h"
#include "entitygroup.h"
#include "vec2f.h"

namespace zen
{
    class World
    {
    public:
        World();
        ~World();

        //void addEntity(Entity* entity);
        void addEntityGroup(EntityGroup* group, float paralaxAmount);

        void update(float frameTime);

        void addPlatformLine(Line* line);

        float getGravity();
        std::vector<Line*>* getPlatformLines();

        EntityGroup* getMainGroup();
    private:
        struct Layer
        {
            EntityGroup* eGroup;
            float paralaxAmount;
        };

        //std::vector<Entity*> entities;
        std::vector<Layer> layers;
        EntityGroup mainGroup;

        float gravity;
    };
}
#endif
