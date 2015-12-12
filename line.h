#ifndef H_LINE
#define H_LINE

#include <SFML/Graphics.hpp>
#include <stdint.h>

#include "vec2f.h"

namespace zen
{
    class Line
    {
    public:
        struct IntersectResult
        {
            bool intersected;
            Vec2f pos;
        };
        Line();
        Line(Vec2f pos0, Vec2f pos1);

        void create(Vec2f pos0, Vec2f pos1);
        void draw(sf::RenderTarget* window);

        Vec2f getPosition(uint8_t index);

        float getMValue();
        float getKValue();
        bool isVertical();
        float calculateYValue(float x);

        //Intersection between 2 perpendicular lines is undefined
        IntersectResult getIntersect(Line* other);
    private:
        void calculateConstants();
        Vec2f pos[2]; 

        bool vertical;

        float mValue;
        float kValue;
        
    };
}
#endif
