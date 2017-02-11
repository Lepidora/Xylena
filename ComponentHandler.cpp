#include "stdafx.h"
#include "ComponentHandler.h"

//Local includes
#include "SpriteRenderComponent.h"

namespace Xylena {

    std::map<ComponentUID, RenderComponent *> ComponentHandler::componentMap;
    ComponentUID ComponentHandler::uidCount = 0;

    RenderComponent * ComponentHandler::defaultRenderComponent = nullptr;

    ComponentUID ComponentHandler::generateUID(RenderComponent * component) {
        
        ComponentUID returnID = uidCount;
        uidCount++;

        componentMap.insert(std::pair<ComponentUID, RenderComponent *>(returnID, component));

        return returnID;
    }

    RenderComponent * ComponentHandler::getDefaultRenderComponent() {
        
        if (defaultRenderComponent == nullptr) {
            return SpriteRenderComponent::getComponent();
        } else {
            return defaultRenderComponent;
        }

    }

    RenderComponent * ComponentHandler::getComponentForUID(ComponentUID id) {

        std::map<ComponentUID, RenderComponent *>::iterator componentLocation = componentMap.find(id);

        if (componentLocation != componentMap.end()) {
            return componentLocation->second;
        } else {
            return nullptr;
        }
    }

}
