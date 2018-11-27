#include "stdafx.h"
#include "Render.h"

//System includes
#include <vector>

//Local includes
#include "Stage.h"
#include "StageHandler.h"
#include "StageCamera.h"
#include "GameObject.h"
#include "Bounds.h"
#include "WindowHandler.h"
#include "ShaderHandler.h"

namespace Xylena {

    ///Initialisation for static sprite rendering queue
    std::queue<RenderSprite> Render::spriteRenderQueue;

    ///Initialisation for static object rendering sorting map

    /*
     * unsigned int - map | 
     *                    v
     *                  float - vector |
     *                                 v
     *                           GameObjectPtr
     */

    /*
        The unsigned int represents the 'level' of rendering, as determined by the GameObject
        This is linked to a map of depth values to determine rendering order
        The depth is a float to enable precise values
        The depth is linked to a vector of the GameObjects to draw
    */
    std::map<ComponentUID, std::map<float, std::vector<GameObjectPtr>>> Render::renderOrderMap;

    VAO Render::vertexArray;
    VAO Render::textureVertexArray;

    VBO Render::textureBuffer;
    
    bool Render::cullOutOfFrame = false;

	Render::Render() {
        Render::vertexArray = 0;
    }

	void Render::initRenderer() {

        //Attempts to initiate GLFW. If it doesn't, it returns immediately
        if (!glfwInit()) {
            throw std::runtime_error("Failed to initialize GLFW\n");
            return;
        }
	}

    void Render::rebindVertexArray(VAO newVertexArray) {

        VAO currentVAO;
        //glGetInteger64v(GL_VERTEX_ARRAY_BINDING, &currentVAO);
        glGetIntegerv(GL_VERTEX_ARRAY_BINDING, (GLint *)&currentVAO);

        if (currentVAO != newVertexArray) {
            glBindVertexArray(newVertexArray);
        }
    }
    
    void Render::setBackgroundColor(int red, int green, int blue, int alpha) {
        glClearColor((red/255.0), (green/255.0), (blue/255.0), (alpha/255.0));
    }

	void Render::render(double interpolation) {
        
		//Get the vector of objects from the currently active stage
		StagePtr currentStage = StageHandler::getCurrentStage();

		if (currentStage != nullptr) {

			std::vector<GameObjectPtr> stageObjects = currentStage->getObjects();

			StageCameraPtr activeCamera = currentStage->getActiveCamera();
			Bounds cameraBounds = activeCamera->calculateBoundsForView();

            //Empty the render order mapping so that it can be recalculated
            renderOrderMap.clear();

			for (size_t stageObjectIndex = 0; stageObjectIndex < stageObjects.size(); stageObjectIndex++) {

				GameObjectPtr currentObject = stageObjects.at(stageObjectIndex);
                
                if ((!cullOutOfFrame || currentObject->getLocation()->isWithin2DBounds(cameraBounds)) && currentObject->isVisible()) {
                    
                    addGameObjectToMap(currentObject);
                }
			}

            //Clear the screen for the next frame to be drawn
            //glClearColor(0.4, 0.1, 0.9, 1.0);
            glClear(GL_COLOR_BUFFER_BIT);
            
            float ratio;
            int width, height;

            //Sets the viewport to be the window size
            glfwGetFramebufferSize(WindowHandler::getMainWindowGLPointer(), &width, &height);
            ratio = width / (float)height;
            glViewport(0, 0, width, height);

            for (auto mapIterator = renderOrderMap.begin(); mapIterator != renderOrderMap.end(); mapIterator++) {

                auto &objectMap = mapIterator->second;
                
                RenderComponent *component = ComponentHandler::getComponentForUID(mapIterator->first);

                if (component) {

                    component->bind();
                    component->preRender();

                    

                    for (auto objectMapIterator = objectMap.begin(); objectMapIterator != objectMap.end(); objectMapIterator++) {

                        std::vector<GameObjectPtr> &objectVector = objectMapIterator->second;

                        //Profiler::start("componentrender");

                        for (size_t i = 0; i < objectVector.size(); i++) {

                            GameObjectPtr gameObject = objectVector[i];
                            
                            
                            
                            //if (!component) {
                                //component = gameObject->getRenderComponent();
                                
                            //}

                            component->render(gameObject.get());

                        }

                        //componentTime = Profiler::stop("componentrender");

                    }

                    

                    component->unbind();

                }

                

            }

            //time_t renderTime = Profiler::stop("rendering") - componentTime;

            //printf("Sort time: %02I64dms Render time: %02I64dms Component time: %02I64dms\n", sortTime, renderTime, componentTime);


		}

        Profiler::start("bufferswap");

		//Render the scene and finish
		glfwSwapBuffers(WindowHandler::getMainWindowGLPointer());

        

		
	}

    void Render::addGameObjectToMap(GameObjectPtr objectPtr) {

        //Expose the pointer for ease of use
        GameObject *object = objectPtr.get();

        //Set up component local variables
        RenderComponent *component = object->getRenderComponent();
        ComponentUID uid = component->getComponentUID();

        //Get object's render level
        float renderLevel = object->getRenderLevel();

        //Find the location of the component UID in the render order map
        auto objectLocation = renderOrderMap.find(uid);

        //If the object doesn't exist in the map
        if (objectLocation == renderOrderMap.end()) {

            //Add a new pair with the component UID and a fresh float/vector map and set the object location to the iterator pointing to it
            objectLocation = renderOrderMap.insert(std::pair<ComponentUID, std::map<float, std::vector<GameObjectPtr>>>(uid, std::map<float, std::vector<GameObjectPtr>>())).first;
        }

        //Get the map at the value of the object location iterator
        auto &objectMapping = objectLocation->second;

        //Find the render level in the map
        auto vectorLocation = objectMapping.find(renderLevel);

        //If the object doesn't exist in the map
        if (vectorLocation == objectMapping.end()) {

            //Add a new pair with the render level and a fresh GameObjectPtr vector and set the vector location to the pair's iterator 
            vectorLocation = objectMapping.insert(std::pair<float, std::vector<GameObjectPtr>>(renderLevel, std::vector<GameObjectPtr>())).first;
        }

        //Add the game object to the vector
        std::vector<GameObjectPtr> &objectVector = vectorLocation->second;
        objectVector.push_back(objectPtr);

    }

    VAO simpleTextureVAO;

	void Render::renderSimpleObject(GameObjectPtr object) {
		if (object.get() != nullptr) {

			TexturePtr objectTexture = object->getTexture();

			if (objectTexture.get() != nullptr) {

			}
		}
	}

    void Render::renderSprite(TexturePtr texturePtr, LocationPtr locationPtr, float rotation, float depth) {

        RenderSprite sprite;

        sprite.locationPtr = locationPtr;
        sprite.texturePtr = texturePtr;
        sprite.rotation = rotation;
        sprite.depth = depth;

        renderSprite(sprite);

    }

    void Render::renderSprite(RenderSprite sprite) {
        if (sprite.texturePtr.get() != nullptr && sprite.locationPtr.get() != nullptr) {
            spriteRenderQueue.push(sprite);
        }
    }
    
    void Render::cullOutOfFrameObjects(bool cull) {
        cullOutOfFrame = cull;
    }
}
