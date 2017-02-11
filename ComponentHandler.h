#pragma once

//System includes
#include <map>

//Local includes
//#include "SpriteRenderComponent.h"

namespace Xylena {

    //typedefs
    typedef unsigned int ComponentUID;

    class RenderComponent;

    class ComponentHandler {
    private:

        static std::map<ComponentUID, RenderComponent *> componentMap;
        

        static ComponentUID uidCount;
        static RenderComponent * defaultRenderComponent;
    public:
        ComponentHandler() {};
        ~ComponentHandler() {};

        static ComponentUID generateUID(RenderComponent * component);

        static void setDefaultRenderComponent(RenderComponent * renderComponent) { defaultRenderComponent = renderComponent; };
        static RenderComponent * getDefaultRenderComponent();

        static RenderComponent * getComponentForUID(ComponentUID id);

    };
}
