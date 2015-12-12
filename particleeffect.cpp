#include "particleeffect.h"

using namespace zen;

ParticleEffect::ParticleEffect()
    :
    texture(nullptr)
{
    float tMax = 3; //TODO Remove
    //Set default functions
    //Kill the particle immedietly after one second
    deathFunction = [tMax](float t, int seed)
    {
        return t > tMax;
    };

    //Constant acceleration upwards
    offsetFunction = [](float t, int seed)
    {
        return Vec2f(0,-100 * t);
    };

    //No rotation
    angleFunction = [](float t, int seed)
    {
        return M_PI;
    };
    
    //Constant keyframe
    keyframeFunction = [](float t, int seed)
    {
        return 0;
    };
    sizeFunction = [](float t, int seed)
    {
        return Vec2f(100,100);
    };
    colorFunction = [tMax](float t, int seed)
    {
        return sf::Color(255, 255, 255, 255);
    };
}
ParticleEffect::ParticleEffect(float frequency)
    : ParticleEffect()
{
    //keyframes.push_back(keyframe);
    setFrequency(frequency);
}

//ParticleEffect* ParticleEffect::clone()
//{
//    return new ParticleEffect(*this);
//}

void ParticleEffect::update(float frameTime)
{
    currentTime += frameTime;
    //Calculating how many particles need to be spawned this frame
    float timeSinceLastSpawn = currentTime - lastSpawned;
    float fParticlesToSpawn = timeSinceLastSpawn / secondsPerParticle;
    int particlesToSpawn = floor(fParticlesToSpawn);
    lastSpawned = currentTime - (fParticlesToSpawn - particlesToSpawn) * secondsPerParticle;

    //std::cout << currentTime << "   " << secondsPerParticle << std::endl;

    //Spawn those particles
    for(int i = 0; i < particlesToSpawn; ++i)
    {
        addParticle();
    }
    
    //Clearing the last list of vertecies
    vertecies.clear();

    for(auto& particle : particles)
    {
        //Increasing the time this particle has been alive
        particle.timeAlive += frameTime;
        
        float timeAlive = particle.timeAlive;
        int seed = particle.seed;

        particle.offset = offsetFunction(timeAlive, seed);
        particle.size = sizeFunction(timeAlive, seed);
        particle.angle = angleFunction(timeAlive, seed);
        particle.color = colorFunction(timeAlive, seed);
        particle.tileID = keyframeFunction(timeAlive, seed);

        //Recalculating the vertecies of the particle
        calculateVertecies(particle);

        //Adding the current particles vertecies to the list of vertecies to be
        //drawn by the draw function
        for(auto it : particle.vertecies)
        {
            vertecies.push_back(it);
        }
    }


    for(std::vector<Particle>::iterator particle = particles.begin(); particle != particles.end(); particle++)
    {
        //Checking if the particle has expired
        if(deathFunction(particle->timeAlive, particle->seed))
        {
            particle = particles.erase(particle) - 1;
        }
    }
}
void ParticleEffect::draw(sf::RenderWindow* window)
{
    sf::RenderStates renderState;
    renderState.texture = texture.get();

    window->draw(vertecies.data(), vertecies.size(), sf::Quads, renderState);
}

void ParticleEffect::setFrequency(float frequency)
{
    this->frequency = frequency;

    this->secondsPerParticle = 1/frequency;
}

void ParticleEffect::setOffsetFunction(std::function<Vec2f(float, int)> offsetFunction)
{
    this->offsetFunction = offsetFunction;
}
void ParticleEffect::setSizeFunction(std::function<Vec2f(float, float)> sizeFunction)
{
    this->sizeFunction = sizeFunction;
}
void ParticleEffect::setKeyframeFunction(std::function<int(float, int)> keyframeFunction)
{
    this->keyframeFunction = keyframeFunction;
}
void ParticleEffect::setDeathFunction(std::function<bool(float, int)> deathFunction)
{
    this->deathFunction = deathFunction;
}
void ParticleEffect::setColorFunction(std::function<sf::Color(float, int)> colorFunction) 
{
    this->colorFunction = colorFunction;
}

void ParticleEffect::setTexture(std::shared_ptr<sf::Texture> texture, Vec2f tileSize, int tileAmount)
{
    this->texture = texture;
    this->tileSize = tileSize;

    calculateTileCoords(tileAmount);
}


////////////////////////////////////////////////////////////////////
//                  Private member methods
////////////////////////////////////////////////////////////////////

void ParticleEffect::addParticle()
{
    float seed = rand();
    Particle newParticle;
    newParticle.seed = seed;
    newParticle.origin = transform.getPosition();
    newParticle.offset = offsetFunction(0, seed);
    newParticle.angle = angleFunction(0, seed);
    newParticle.size = sizeFunction(0, seed);
    
    particles.push_back(newParticle);

    //Create 4 vertecies
    for(int i = 0; i < 4; ++i)
    {
        particles.back().vertecies.push_back(sf::Vertex(Vec2f(0,0), Vec2f(0,0)));
    }

    for(auto& it : particles.back().vertecies)
    {
        it.color = sf::Color(255,255,0,100);
    }
}

void ParticleEffect::calculateVertecies(Particle& particle)
{
    Vec2f position = particle.offset + particle.origin;
    int tileID = particle.tileID;

    float currAngle = M_PI / 4 + particle.angle;

    for(auto& it : particle.vertecies)
    {
        it.position.x = position.x + particle.size.x / 2 * cos(currAngle);
        it.position.y = position.y + particle.size.y / 2 * sin(currAngle);

        it.color = particle.color;

        currAngle += M_PI / 2;
    }

    if(texture.get() != nullptr)
    {
        std::pair<Vec2f, Vec2f> texCoord = texCoordIndexMap[tileID % texCoordIndexMap.size()];

        particle.vertecies[0].texCoords = texCoord.first;
        particle.vertecies[1].texCoords = Vec2f(texCoord.first.x, texCoord.second.y);
        particle.vertecies[2].texCoords = texCoord.second;
        particle.vertecies[3].texCoords = Vec2f(texCoord.second.x, texCoord.first.y);
    }
}
void ParticleEffect::calculateTileCoords(int tileAmount) 
{
    float xCoord = 0;
    float yCoord = 0;
    for(int i = 0; i < tileAmount; ++i)
    {
        //Calculate the other end of the tile
        Vec2f newCoord = Vec2f(xCoord + tileSize.x, yCoord + tileSize.y);

        //If this tile is outside the of the texture
        if(newCoord.x > texture->getSize().x)
        {
            xCoord = 0;
            yCoord += tileSize.y;
        }
        std::pair<Vec2f, Vec2f> texCoords;
        texCoords.first = Vec2f(xCoord, yCoord);
        texCoords.second = Vec2f(xCoord + tileSize.x, yCoord + tileSize.y);

        texCoordIndexMap.push_back(texCoords);
        
        xCoord += tileSize.x;
    }
}
