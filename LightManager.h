#ifndef H_LIGHT_MANAGER
#define H_LIGHT_MANAGER

#include <vector>
#include <queue>
#include <memory>

#include "Light.h"
#include "IDList.h"

namespace zen
{
    class LightManager
    {
    public:
        /*
         *  Add a new light to be managed
         */
        int addLight(Light* light);

        /*
         *  Remove a light from the list. This does not run delete so that needs to be done elsewhere
         */
        void forgetLight(int id);

        std::size_t lightAmount();
        
        std::vector<Light*> getLightVector();
        std::vector<float> getRanges();
        std::vector<sf::Color> getColors();
        std::vector<Vec2f> getPositions();
    private:
        void tryRegenerateLists();

        IDList<Light> lights;

        bool listHasChanged = true;

        std::vector<Light*> lightVector;
        std::vector<float> ranges;
        std::vector<sf::Color> colors;
        std::vector<Vec2f> positions;
    };
} /* zen */ 
#endif
