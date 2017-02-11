#pragma once

//System includes
#include <vector>

//Local includes
#include "Window.h"
#include "Stage.h"

namespace Xylena {

    class Mouse {
    private:
        static double xPos;
        static double yPos;
        
        static std::vector<GameObjectPtr> previousObjects;

        static void queryMousePos();
    public:
        Mouse() {};
        ~Mouse() {};

        static void registerWindow(Window *window);
        static void setPosValues(double x, double y);

        static void setMousePosition(Window *window, double x, double y);
        static void setMousePosition(double x, double y);

        static Coordinate mousePositionToWorld();

        static double getX();
        static double getY();
        
        static void processMouseEvents();
        static void processMouseEvents(StagePtr stage);
        
    };
}