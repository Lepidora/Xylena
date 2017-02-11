#include "stdafx.h"
#include "Input.h"

#include "InputComponent.h"

void processKey(GLFWwindow * window, int key, int scancode, int action, int mods) {
    Xylena::InputEvent inputEvent;
    inputEvent.setKeyCode(Xylena::InputEvent::keyCodeForKeyboard(key));

    Xylena::KeyStatus status = Xylena::InputEvent::keyStatusForAction(action);
    inputEvent.setKeyStatus(status);

    Xylena::Input::addEventToQueue(inputEvent);
}

void processMouse(GLFWwindow * window, int button, int action, int mods) {
    Xylena::InputEvent inputEvent;
    inputEvent.setKeyCode(Xylena::InputEvent::keyCodeForMouse(button));
    
    Xylena::KeyStatus status = Xylena::InputEvent::keyStatusForAction(action);
    inputEvent.setKeyStatus(status);
    
    Xylena::Input::addEventToQueue(inputEvent);
    Xylena::Input::addMouseEventToQueue(inputEvent);
    
}



namespace Xylena {

    std::map<KeyCode, InputComponent *> Input::inputRegistry;
    std::queue<InputEvent> Input::inputQueue;
    std::vector<InputEvent> Input::mouseEvents;

    void Input::registerWindow(Window *window) {

        glfwSetKeyCallback(window->getGLFWwindowPtr().get(), processKey);
        glfwSetMouseButtonCallback(window->getGLFWwindowPtr().get(), processMouse);

    }

    void Input::registerEvent(InputComponent * component, InputEvent input) {

        std::pair<KeyCode, InputComponent *> pair(input.getKeyCode(), component);
        inputRegistry.insert(pair);
    }

    void Input::addEventToQueue(InputEvent input) {
        inputQueue.push(input);
    }
    
    void Input::addMouseEventToQueue(InputEvent input) {
        mouseEvents.push_back(input);
    }

    void Input::addKeyToQueue(KeyCode code) {
        InputEvent input;
        input.setKeyCode(code);

        addEventToQueue(input);
    }

	void Input::processInput() {

        while (!inputQueue.empty()) {

            InputEvent input = inputQueue.front();

            auto searchIt = inputRegistry.find(input.getKeyCode());
            if (searchIt != inputRegistry.end()) {
                InputComponent *component = searchIt->second;
                component->pushEvent(input);
            }

            inputQueue.pop();
        }
	}
    
    std::vector<InputEvent> * Input::getMouseEvents() {
        return &mouseEvents;
    }
}