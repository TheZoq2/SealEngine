#ifndef H_ENTITYGROUP
#define H_ENTITYGROUP

#include <vector>
#include <stdint.h>

#include <SFML/Graphics.hpp>

#include "entity.h"
#include "platform.h"
#include "systems/System.h"
#include "exceptions/MissingSystemException.h"
#include "LightManager.h"

namespace zen
{
    class Entity;
    class System;

    class EntityGroup
    {
    public:
        static const uint32_t NO_PLATFORM = (uint32_t) -1;

        struct PlatformCollisionResult
        {
            uint32_t platformID;
            Line::IntersectResult intResult;
        };
        struct IDPlatform
        {
            uint32_t id;
            Platform* platform;
        };

        EntityGroup();

        //TODO: Make sure entity is only added once
        void addEntity(Entity* entity);
        int addPlatform(Platform* platform);

        void update(float frameTime);

        void draw(sf::RenderTarget* target);

        void onEntityDepthChange(Entity* entity);

        std::vector<IDPlatform> getPlatforms();
        Platform* getPlatformByID(uint32_t id);
        bool platformExists(uint32_t id);
        LightManager* getLightManager();


        PlatformCollisionResult getPlatformCollision(Vec2f originPos, Line* line); 
        Entity* getFirstCollision(Vec2f point);
    
        template<class T>
        void addSystem(std::unique_ptr<T> system)
        {
            //Ensure that the system is actually a system
            static_assert(std::is_base_of<System, T>::value, "System needs to be a subclass of the System class");

            system->setOwner(this);
            systems.insert(std::make_pair(std::type_index(typeid(T)), std::move(system)));
        }

        template<class T>
        System* getSystem()
        {
            //Ensure that the object passed is an instance of component
            static_assert(std::is_base_of<System, T>::value, "System class need to be subclass of System");

            if(systems.find(typeid(T)) == systems.end())
            {
                //TODO: Add exceptions
                //throw MissingSystemException(typeid(T));
            }

            return dynamic_cast<T*>(systems[typeid(T)].get());
        }
    private:
        uint32_t nextPlatformID;

        //Insert an entity in the correct location in the entity vector based on depth
        void insertEntity(Entity* entity); 

        std::vector< std::unique_ptr< Entity > > entities;
        std::vector< std::unique_ptr< int > > test;
        std::vector<IDPlatform> platforms;

        //std::vector<std::unique_ptr<System>> systems;
        std::map<std::type_index, std::unique_ptr<System>> systems;

        LightManager lightManager;
    };
}
#endif
