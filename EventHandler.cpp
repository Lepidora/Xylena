#include "EventHandler.h"

//Local includea
#include "StageHandler.h"
#include "Mouse.h"

namespace Xylena {
    
    std::unordered_set<GameObject *> EventHandler::registeredObjects;
    std::unordered_set<GameObject *> EventHandler::previousObjects;
    
    std::unordered_set<GameObject *> EventHandler::currentDown;
    
    //std::vector<InputEvent> EventHandler::mouseEvents;
    
    void EventHandler::processEvents() {
        processMouseEvents();
    }
    
    void EventHandler::processMouseEvents() {
        
        std::vector<InputEvent> * mouseEvents = Input::getMouseEvents();
        
        StagePtr stage = StageHandler::getCurrentStage();
        
        std::vector<GameObjectPtr> stageObjects = stage->getObjects();
        
        double mouseX = Mouse::getX();
        double mouseY = Mouse::getY();
        
        Coordinate mouseCoord = Mouse::mousePositionToWorld();
        
        std::unordered_set<GameObject *> hits;
        
        for (int i = 0; i < stageObjects.size(); i++) {
            
            GameObject *currentObject = stageObjects[i].get();

            if (registeredObjects.find(currentObject) != registeredObjects.end()) {
                
                LocationPtr objectLocation = currentObject->getLocation();
                
                if (objectLocation->isPointWithin2DBounds(mouseCoord)) {
                    hits.insert(currentObject);
                }
            }
        }
        
        for (GameObject *object: hits) {
            
            if (object) {
                if (previousObjects.find(object) == previousObjects.end()) {
                    object->mouseEnter(mouseX, mouseY, false);
                    #warning You don't order for topness
                    
                } else {
                    object->mouseOver(mouseX, mouseY, false);
                }
                
                for (InputEvent &event: *mouseEvents) {
                    
                    KeyCode code = event.getKeyCode();
                    KeyStatus status = event.getKeyStatus();
                    
                    if (status == KEY_PRESS) {
                        
                        currentDown.insert(object);
                        
                        object->mouseDown(code, mouseX, mouseY, false);
                        
                    }
                    
                    if (status == KEY_RELEASE) {
                        
                        object->mouseUp(code, mouseX, mouseY, false);
                        
                        if (currentDown.find(object) != currentDown.end()) {
                            object->onClick(code, mouseX, mouseY, false);
                            currentDown.erase(object);
                        }
                        
                    }
                    
                }
                
            }
        }
        
        for (GameObject *object: previousObjects) {
            if (object) {
                if (hits.find(object) == hits.end()) {
                    if (object != nullptr) {
                        object->mouseLeave(mouseX, mouseY, false);
                    }
                    currentDown.erase(object);
                }
            }
        }
        
        previousObjects = hits;
        mouseEvents->clear();
        
    }
    
    void EventHandler::registerMouseEvent(GameObject *object) {
        registeredObjects.insert(object);
    }
    
    void EventHandler::unregisterMouseEvent(GameObject *object) {
        registeredObjects.erase(object);
    }
    
    void EventHandler::removeObject(GameObject *object) {
        registeredObjects.erase(object);
        previousObjects.erase(object);
        currentDown.erase(object);
    }
    
}