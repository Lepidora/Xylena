#pragma once

//System includes
#include <queue>

//Local includes
#include "InputEvent.h"
#include "Input.h"

namespace Xylena {

    class GameObject;

	class InputComponent {
    protected:
        std::queue<InputEvent> inputQueue;
	public:
        virtual ~InputComponent() {};
		virtual void process(GameObject *gameObject) = 0;
        virtual void pushEvent(InputEvent input) { inputQueue.push(input.clone()); };
        virtual void init() {};
        virtual void registerEvent(InputEvent input) { Input::registerEvent(this, input); };

	};
}
