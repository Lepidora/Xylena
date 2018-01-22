#include "stdafx.h"
#include "GameObject.h"

//System includes
#define _USE_MATH_DEFINES
#include <math.h>
#include <cmath>

//Local includes
#include "Render.h"
#include "ComponentHandler.h"
#include "TextureHandler.h"
#include "StageHandler.h"
#include "Mouse.h"
#include "StageCamera.h"
#include "EventHandler.h"
#include "LuaHandler.h"
#include "Transaction.h"

namespace Xylena {
    
    unsigned long int GameObject::uidCounter = 0;
    
    GameObject::GameObject() {
        
        setLocation(LocationPtr(new Location));
        setTexture(TexturePtr(new Texture));
        setRenderComponent(ComponentHandler::getDefaultRenderComponent());
        setRenderLevel(0.0);
        
        setVisibility(true);
        setTextureOffset(0.0, 0.0);
        setTextureRotation(0.0);
        
        //printf("UID: %lu\n", uidCounter);
        
        uid = GameObject::uidCounter;
        GameObject::uidCounter++;
        
    }
    
    GameObject::GameObject(std::string scriptLocation): GameObject() {
        script = ScriptPtr(new Script(scriptLocation));
        initialise();
        callScriptFunction(createSelector);
    }
    
    GameObject::~GameObject() {
        EventHandler::removeObject(this);
    }

	void GameObject::setVisibility(bool _visible) {
		visible = _visible;
	}

	bool GameObject::isVisible() {
		return visible;
	}

	//Allows for setting up information before the main update method
	void GameObject::preUpdate() {}

	//Main update method. Most code should be here
	void GameObject::update() {
        callScriptFunction(getSelector("update"));
    }

	//Allows for performing additional actions after update
	void GameObject::postUpdate() {}

    void GameObject::setTexture(const char * filename) {
        Texture *texture = TextureHandler::createTextureFromFile(filename);
        setTexture(TexturePtr(texture));
    }

    void GameObject::setPosition(float x, float y) {
        location->setCoordinates(Coordinate(x, y, 0.0));
    }

    void GameObject::setPosition(float x, float y, float z) {
        location->setCoordinates(Coordinate(x, y, z));
    }
    
    void GameObject::setPosition(Coordinate position) {
        location->setCoordinates(Coordinate(position.getX(), position.getY(), position.getZ()));
    }

    Coordinate GameObject::getPosition() {
        return location->getCoordinates();
    }

    void GameObject::translatePosition(float x, float y) {
        translatePosition(x, y, 0);
    }

    void GameObject::translatePosition(float x, float y, float z) {
        Coordinate pos = getPosition();
        setPosition(pos.getX() + x, pos.getY() + y, pos.getZ() + z);
    }

    void GameObject::setSize(float width, float height) {
        location->setSize(Coordinate(width, height, 0.0));
    }

    void GameObject::setSize(float width, float height, float depth) {
        location->setSize(Coordinate(width, height, depth));
    }

    Coordinate GameObject::getSize() {
        return location->getSize();
    }
    
    unsigned long int GameObject::getUID() {
        return uid;
    }
    
    void GameObject::destroy() {
        stage->removeObject(this);
    }

    void GameObject::pointToMouse() {
        
        Coordinate mouseWorldPos = Mouse::mousePositionToWorld();
        Coordinate objectWorldPos = getLocation()->getCoordinates();

        float objectX = objectWorldPos.getX();
        float objectY = objectWorldPos.getY();

        float mouseX = mouseWorldPos.getX();
        float mouseY = mouseWorldPos.getY();

        float normalisedMouseX = mouseX - objectX;
        float normalisedMouseY = mouseY - objectY;

        float normalisedObjectX = 0.0;
        float normalisedObjectY = 1.0;

        float dotProduct = (normalisedMouseX * normalisedObjectX) + (normalisedMouseY * normalisedObjectY);
        float determinant = (normalisedMouseX * normalisedObjectY) - (normalisedMouseY * normalisedObjectX);

        float offsetAngle = std::atan2(dotProduct, determinant);
        float offsetDegreeAngle = offsetAngle * (180 / M_PI);
        float degreeAngle = offsetDegreeAngle;
        setRotation(degreeAngle);
        
        //printf("Mouse: x: %g, y: %g\n", mouseX, mouseY);
        //printf("World: x: %g, y: %g\n", mouseX, mouseY);
        //printf("Offset: %g\n", offsetDegreeAngle);
        //printf("Angle: %g\n", degreeAngle);
        
    }
    
    void GameObject::onClick(KeyCode button, double mouseX, double mouseY, bool top) {};
    void GameObject::mouseDown(KeyCode button, double mouseX, double mouseY, bool top) {};
    void GameObject::mouseUp(KeyCode button, double mouseX, double mouseY, bool top) {};
    
    void GameObject::mouseOver(double mouseX, double mouseY, bool top) {};
    void GameObject::mouseEnter(double mouseX, double mouseY, bool top) {};
    void GameObject::mouseLeave(double mouseX, double mouseY, bool top) {};
    
    void GameObject::initialise() {
        
        void (GameObject::*translatePositionFptr)(float, float) = &GameObject::translatePosition;
        bool (GameObject::*getVisibilityFptr)() = &GameObject::isVisible;
        void (GameObject::*setVisibilityFptr)(bool) = &GameObject::setVisibility;
        void (GameObject::*setRotationFptr)(double) = &GameObject::setRotation;
        double (GameObject::*getRotationFptr)() = &GameObject::getRotation;
        
        StatePtr st = script->getState();
        //script->test(1);
        
        script->addObject(std::string("self"), *this,
                          "getVisibility", getVisibilityFptr,
                          "setVisibility", setVisibilityFptr,
                          "translatePosition", translatePositionFptr,
                          "setRotation", setRotationFptr,
                          "getRotation", getRotationFptr
                          );
        
        createSelector = getSelector("create");
        updateSelector = getSelector("update");
    }

}