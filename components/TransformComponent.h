#ifndef H_TRANSFORM_COMPONENT
#define H_TRANSFORM_COMPONENT

#include "Component.h"

namespace zen
{
    class TransformComponent : public Component
    {
    public:
        //A list of all the messages that can be sent by this component
        enum Messages
        {
            POSITION_CHANGED,
            SCALE_CHANGED,
            ANGLE_CHANGED
        };

        void setPosition(Vec2f position);
        void setPosition(float x, float y);
        void setScale(Vec2f scale);
        void setScale(float x, float y);
        void setAngle(float angle);

        Vec2f getPosition();
        Vec2f getScale();
        float getAngle();
    private:
        Vec2f position = Vec2f(0,0);
        Vec2f scale = Vec2f(0, 0);
        float angle = 0;
    };
}
#endif
