#pragma once

//Local includes
#include "ComponentHandler.h"
#include "GLTypes.h"

namespace Xylena {

    class GameObject;
    class StageCamera;

    class RenderComponent {
    protected:
        VAO renderVAO;

    public:
        RenderComponent() {};
        ~RenderComponent() {};

        virtual void bind() = 0;
        virtual void unbind() = 0;
        virtual void preRender() {};
        virtual void render(GameObject *gameObject) = 0;

        virtual ComponentUID getComponentUID() = 0;

        //This is static because subclasses initialise their own instance of it when they are created. Although it is functionally useless, it reminds me to not keep meddling with getting components when I forget how the system works
        //static RenderComponent *component;
    };
}
