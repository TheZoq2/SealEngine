#ifndef H_ZEN_LIGHT
#define H_ZEN_LIGHT

#include "vec2f.h"

namespace zen
{
    class Light
    {
    public:
        Light() = default;
        Light(Vec2f position, sf::Color color, float range);

        void setPosition(Vec2f position);

        Vec2f getPosition();
        sf::Color getColor();
        float getRange();
    
    private:
        Vec2f position;

        sf::Color color;
        
        float range = 0;
    };
} /* zen */ 

#endif
