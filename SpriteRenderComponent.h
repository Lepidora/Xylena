#pragma once

//GLM includes
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//Local includes
#include "RenderComponent.h"

namespace Xylena {

    class SpriteRenderComponent : public RenderComponent {
    private:
        static SpriteRenderComponent *component;
        ComponentUID uid;

        VBO renderVBO;
        EBO renderEBO;

        glm::mat4 ortho;

        ShaderProgram program;

        void initRenderer();

    public:
        SpriteRenderComponent();
        ~SpriteRenderComponent() {};

        void bind();
        void unbind();

        void preRender();
        void render(GameObject *gameObject);

        ComponentUID getComponentUID() { return uid; }

        static SpriteRenderComponent* getComponent();

    };
}
