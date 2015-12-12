#ifndef H_PARTICLEEFFECT
#define H_PARTICLEEFFECT

#include <memory>

#include "vec2f.h"
#include "keyframeval.h"
#include "components/TransformComponent.h"

namespace zen
{
    class ParticleEffect
    {
    public:
        ParticleEffect(float frequency);
        ParticleEffect();

        ParticleEffect* clone();
        
        //TODO READD
        //ParticleEffect(float frequency);

        virtual void draw(sf::RenderWindow* window);
        virtual void update(float frameTime);

        void setFrequency(float frequency);
        void setOffsetFunction(std::function<Vec2f(float, int)> offsetFunction);
        void setSizeFunction(std::function<Vec2f(float, float)> sizeFunction);
        void setKeyframeFunction(std::function<int(float, int)> keyframeFunction);
        void setDeathFunction(std::function<bool(float, int)> deathFunction);
        void setColorFunction(std::function<sf::Color(float, int)> colorFunction);

        void setTexture(std::shared_ptr<sf::Texture> texture, Vec2f tileSize, int tileAmount);
    private:
        struct Particle
        {
            float timeAlive;
            int seed; //Random number used to add variation between particles

            Vec2f origin; //The starting point of this specific particle
            Vec2f offset;
            Vec2f size; 
            float angle;
            sf::Color color;

            std::vector<sf::Vertex> vertecies;
            int tileID;
        };


        void addParticle();
        void calculateVertecies(Particle& particle);
        void calculateTileCoords(int tileAmount);

        /*
         * Function that returns true if the particle should be deleted
         */
        std::function<bool(float, int)> deathFunction;
        /*
         *  Function that decides the acceleration at the current lifetime of a particle
         */
        std::function<Vec2f(float, int)> offsetFunction;
        /*
         *  Decides the change in angle of the particle at the specified keyframe
         */
        std::function<float(float, int)> angleFunction;
        /*
         *  Decides the size of the particle over time
         */
        std::function<Vec2f(float, int)> sizeFunction;
        /*
         *  Decides the current keyframe of the particle at the specified time.
         *  Return an integer < the amount of keyframes indicating the index of 
         *  the specified keyframe
         */
        std::function<int(float, int)> keyframeFunction;
        
        /*
         *  Decides the colour over time for the particles
         */
        std::function<sf::Color(float, int)> colorFunction;
        
        //Emitter parameters
        float currentTime;
        float frequency; //Particles created per second
        float secondsPerParticle; //The time in miliseconds between particle spawns
        TransformComponent transform;

        float lastSpawned;

        std::vector<Particle> particles;

        //Vector containing all the vertecies for all the particles currently being 
        //drawn. This is cleared and rebuilt evey time the update function is run 
        std::vector<sf::Vertex> vertecies;

        std::shared_ptr<sf::Texture> texture;
        Vec2f tileSize;
        std::vector<std::pair<Vec2f, Vec2f>> texCoordIndexMap;
    };
}
#endif
