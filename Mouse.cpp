#include "stdafx.h"
#include "Mouse.h"

//Local includes
#include "WindowHandler.h"
#include "StageHandler.h"
#include "StageCamera.h"

void cursorPosCallback(GLFWwindow *window, double x, double y) {
    Xylena::Mouse::setPosValues(x, y);
}

namespace Xylena {

    double Mouse::xPos;
    double Mouse::yPos;
    
    std::vector<GameObjectPtr> Mouse::previousObjects;

    void Mouse::queryMousePos() {
        double x;
        double y;

        glfwGetCursorPos(WindowHandler::getMainWindowGLPointer(), &x, &y);

        xPos = x;
        yPos = y;
    }

    void Mouse::registerWindow(Window *window) {
        glfwSetCursorPosCallback(window->getGLFWwindowPtr().get() , cursorPosCallback);
    }

    void Mouse::setPosValues(double x, double y) {
        xPos = x;
        yPos = y;
    }

    void Mouse::setMousePosition(Window * window, double x, double y) {
        glfwGetCursorPos(window->getGLFWwindowPtr().get(), &x, &y);
    }

    void Mouse::setMousePosition(double x, double y) {
        setMousePosition(WindowHandler::getMainWindow().get(), x, y);
    }

    Coordinate Mouse::mousePositionToWorld() {
        
        StageCameraPtr activeCamera = StageHandler::getCurrentStage()->getActiveCamera();

        float scaleFactor = activeCamera->getScalingFactor();
        
        Coordinate windowSize = WindowHandler::getMainWindow()->getWindowSize();
        Coordinate viewportSize = activeCamera->getViewportSize();
        
        double xCorrect = viewportSize.getX() / windowSize.getX();
        double yCorrect = viewportSize.getY() / windowSize.getY();

        double mouseX = Mouse::getX() * scaleFactor * xCorrect;
        double mouseY = Mouse::getY() * scaleFactor * yCorrect;

        Coordinate cameraTopLeft = activeCamera->calculateTopLeftForView();
        Coordinate mouseWorldPos(cameraTopLeft.getX() + mouseX, cameraTopLeft.getY() + mouseY);

        return mouseWorldPos;
    }

    double Mouse::getX() {
        return xPos;
    }

    double Mouse::getY() {
        return yPos;
    }
    
    void Mouse::processMouseEvents() {
        processMouseEvents(StageHandler::getCurrentStage());
    }
    
    void Mouse::processMouseEvents(StagePtr stage) {
        std::vector<GameObjectPtr> stageObjects = stage->getObjects();
        
        double mouseX = Mouse::getX();
        double mouseY = Mouse::getY();
        
        Coordinate mouseCoord(mouseX, mouseY);
        
        for (int i = 0; i < stageObjects.size(); i++) {
            GameObjectPtr currentObject = stageObjects[i];
            LocationPtr objectLocation = currentObject->getLocation();
            
            if (objectLocation->isPointWithin2DBounds(mouseCoord)) {
                
            }
        }
        
    }
}