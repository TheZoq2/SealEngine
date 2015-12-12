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

        int lightAmount();
    private:
        IDList<Light> lights;

        bool listHasChanged = true;
    };
} /* zen */ 
#endif
