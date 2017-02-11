#pragma once

//System includes
#include <map>
#include <queue>

//Local includes
#include "Window.h"
#include "InputEvent.h"

namespace Xylena {

    class InputComponent;

	class Input {
    private:
        static std::map<KeyCode, InputComponent *> inputRegistry;
        static std::queue<InputEvent> inputQueue;
        
        static std::vector<InputEvent> mouseEvents;
        
	public:
        Input() {};
        ~Input() {};

        static void registerWindow(Window *window);
        static void registerEvent(InputComponent * component, InputEvent input);
        static void addEventToQueue(InputEvent input);
        static void addMouseEventToQueue(InputEvent input);
        static void addKeyToQueue(KeyCode code);
		static void processInput();
        
        static std::vector<InputEvent> * getMouseEvents();

	};
}

void processKey(GLFWwindow * window, int key, int scancode, int action, int mods);
void processMouse(GLFWwindow * window, int button, int action, int mods);