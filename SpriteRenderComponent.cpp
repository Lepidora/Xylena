#include "stdafx.h"
#include "SpriteRenderComponent.h"

#include "OpenGL.h"

//GLM includes
#include "glm/gtx/string_cast.hpp"

//Local includes
#include "Render.h"
#include "StageCamera.h"
#include "StageHandler.h"
#include "ShaderHandler.h"
#include "WindowHandler.h"

//Shader includes
#include "DefaultShaders.h"

namespace Xylena {
    
    SpriteRenderComponent *SpriteRenderComponent::component = nullptr;

    SpriteRenderComponent::SpriteRenderComponent() {

        uid = ComponentHandler::generateUID(this);
        initRenderer();
        
    }

    const float textureVertices[]{
        //  X      Y     Z       U      V
        -1.0f,  1.0f, 0.0f,   0.0f, 1.0f,
        -1.0f, -1.0f, 0.0f,   0.0f, 0.0f,
         1.0f, -1.0f, 0.0f,   1.0f, 0.0f,
         1.0f,  1.0f, 0.0f,   1.0f, 1.0f
    };

    GLuint arrayElements[] = {
        0, 1, 2,
        2, 3, 0
    };

    void SpriteRenderComponent::initRenderer() {
    
        //printf("Function: %p\n", (void *)&glGenVertexArrays);

        VAO textureArrayID;
        glGenVertexArrays(1, &textureArrayID);
        glBindVertexArray(textureArrayID);

        //ShaderProgram textureProgram = ShaderHandler::createProgram("simple", "Simple.vert", "Simple.frag");
        ShaderProgram textureProgram = ShaderHandler::compileProgram("texture", defaultTextureVert, defaultTextureFrag);
        glUseProgram(textureProgram);

        VBO vertexBufferID;
        EBO elementArrayID;

        glGenBuffers(1, &vertexBufferID);
        glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);

        glBufferData(GL_ARRAY_BUFFER, sizeof(textureVertices), textureVertices, GL_STATIC_DRAW);

        glGenBuffers(1, &elementArrayID);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementArrayID);

        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(arrayElements), arrayElements, GL_STATIC_DRAW);
        
        //glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), textureVertices, GL_STATIC_DRAW);

        ShaderAttribute worldPositionAttribute = ShaderHandler::getAttribute(textureProgram, "worldspacePosition");

        glEnableVertexAttribArray(worldPositionAttribute);
        glVertexAttribPointer(worldPositionAttribute, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GL_FLOAT), NULL);

        ShaderAttribute vertexUV = ShaderHandler::getAttribute(textureProgram, "vertexUV");

        glEnableVertexAttribArray(vertexUV);
        glVertexAttribPointer(vertexUV, 2, GL_FLOAT, GL_TRUE, 5 * sizeof(GL_FLOAT), (const GLvoid*)(3 * sizeof(GLfloat)));

        ShaderUniform textureSampler = ShaderHandler::getUniform(textureProgram, "textureSampler");
        glUniform1i(textureSampler, 0);


        //glActiveTexture(GL_TEXTURE0);

        //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        glBindVertexArray(0);

        renderVBO = vertexBufferID;
        renderVAO = textureArrayID;
        renderEBO = elementArrayID;
        program = textureProgram;
    
    }

    void SpriteRenderComponent::bind() {
        glBindVertexArray(renderVAO);
        //printf("BIND\n");
    }

    void SpriteRenderComponent::unbind() {
        glBindVertexArray(NULL);
        //printf("UNBIND\n");
    }

    /*static const GLfloat g_vertex_buffer_data[] = {
        -1.0f, -1.0f, 0.0f,
        1.0f, -1.0f, 0.0f,
        0.0f,  1.0f, 0.0f,
    };*/

    void SpriteRenderComponent::preRender() {

        Coordinate windowSize = WindowHandler::getMainWindow()->getWindowSize();
        StageCameraPtr camera = StageHandler::getCurrentStage()->getActiveCamera();

        //ortho = glm::ortho(0.0f, windowSize.getX(), windowSize.getY(), 0.0f, -1.0f, 1.0f);
        //ortho = glm::ortho(0.0f, viewportX * scalingFactor, viewport.getY() * scalingFactor, 0.0f, -1.0f, 1.0f);
        Coordinate viewport = camera->getViewportSize();
        float scalingFactor = camera->getScalingFactor();

        float viewportX = viewport.getX();
        float viewportY = viewport.getY();
        ortho = glm::ortho(0.0f, viewportX * scalingFactor, viewportY * scalingFactor, 0.0f, -1.0f, 1.0f);
        //ortho = glm::ortho((float)(viewportX * scalingFactor * 1.5), (float)(viewportX * scalingFactor * 0.5), (float)(viewportY * scalingFactor * 0.5), (float)(viewportY * scalingFactor * 1.5), -1.0f, 1.0f);

        //printf("");

        //printf("%s\n", glm::to_string(ortho));
    }

    void SpriteRenderComponent::render(GameObject *gameObject) {
        
        /*float ratio;
        int width, height;

        glfwGetFramebufferSize(WindowHandler::getMainWindowGLPointer(), &width, &height);
        ratio = width / (float)height;
        glViewport(0, 0, width, height);

        //glClearColor(red / 255, green / 255, blue / 255, 1.0);
        //glClear(GL_COLOR_BUFFER_BIT);

        glBindBuffer(GL_ARRAY_BUFFER, renderVBO);
        // Give our vertices to OpenGL.
        glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, renderVBO);
        glVertexAttribPointer(
            0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
            3,                  // size
            GL_FLOAT,           // type
            GL_FALSE,           // normalized?
            0,                  // stride
            (void*)0            // array buffer offset
            );
        // Draw the triangle !
        glDrawArrays(GL_TRIANGLES, 0, 3); // Starting from vertex 0; 3 vertices total -> 1 triangle
        glDisableVertexAttribArray(0);*/

        StageCameraPtr stageCamera = StageHandler::getCurrentStage()->getActiveCamera();

        float objectRotation = gameObject->getRotation();
        float textureRotation = gameObject->getTextureRotation();

        float rotationSum = objectRotation + textureRotation;

        float rotation = 0.0;

        if (rotationSum != 0) {
            rotation = fmod((objectRotation + textureRotation), 360);
        }

        LocationPtr objLocation = gameObject->getLocation();

        Coordinate objCoords = objLocation->getCoordinates();

        float objX = objCoords.getX();
        float objY = objCoords.getY();
        float objZ = objCoords.getZ();

        LocationPtr cameraLocation = stageCamera->getLocation();
        Coordinate cameraCoords = cameraLocation->getCoordinates();

        float scalingFactor = stageCamera->getScalingFactor();

        float camX = cameraCoords.getX();
        float camY = cameraCoords.getY();
        //float camZ = cameraCoords.getZ();

        Coordinate cameraSize = stageCamera->getViewportSize();

        float camXOffset = cameraSize.getX() * scalingFactor;
        float camYOffset = cameraSize.getY() * scalingFactor;

        Coordinate objectSize = objLocation->getSize();
        
        TexturePtr objectTexture = gameObject->getTexture();

        float objectTexX = gameObject->getTextureXOffset();
        float objectTexY = gameObject->getTextureYOffset();

        //glEnableVertexAttribArray(0);
        //glBindBuffer(GL_ARRAY_BUFFER, renderVBO);

        /*glVertexAttribPointer(
            0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
            3,                  // size
            GL_FLOAT,           // type
            GL_FALSE,           // normalized?
            0,                  // stride
            (void*)0            // array buffer offset
            );*/

        
        glm::mat4 spriteMatrix;

        spriteMatrix = spriteMatrix * ortho;

        spriteMatrix = glm::translate(spriteMatrix, glm::vec3(objX + objectTexX + (camXOffset / 2.0) - camX, objY + objectTexY + (camYOffset / 2.0) - camY, objZ));
        
        //spriteMatrix = glm::translate(spriteMatrix, glm::vec3(0.5f * objectSize.getX(), 0.5f * objectSize.getY(), 0.0f));
        spriteMatrix = glm::rotate(spriteMatrix, glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f));
        //spriteMatrix = glm::translate(spriteMatrix, glm::vec3(-0.5f * objectSize.getX(), -0.5f * objectSize.getY(), 0.0f));

        spriteMatrix = glm::scale(spriteMatrix, glm::vec3(objectSize.getX()/2, objectSize.getY()/2, 1.0f));

        //spriteMatrix * ortho;



//#error not finished
        
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        ShaderUniform scaleMatrixUniform = ShaderHandler::getUniform(program, "positioner");
        glUniformMatrix4fv(scaleMatrixUniform, 1, false, glm::value_ptr(spriteMatrix));

        //spriteMatrix = glm::rotate(spriteMatrix, glm::radians(rotation), glm::vec3(-0.5, -0.5, 0.0));

        glActiveTexture(GL_TEXTURE0);

        glBindTexture(GL_TEXTURE_2D, objectTexture->getNextTexture());
        
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        //printf("RENDER\n");

        //glDrawArrays(GL_TRIANGLES, 0, 6);
        //glDrawArrays(GL_TRIANGLES, 0, 3);

        //glDisableVertexAttribArray(0);


        //glBindBuffer(GL_ARRAY_BUFFER, 0);
        


        //Render::renderSprite(gameObject.getTexture(), gameObject.getLocation(), rotation, gameObject.getRenderLevel());
    }

    SpriteRenderComponent * SpriteRenderComponent::getComponent() {
        if (!component) {
            component = new SpriteRenderComponent();
        }

        return component;
    }

}

