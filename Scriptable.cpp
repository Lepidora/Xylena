#include "Scriptable.h"

//Local includes
#include "LuaHandler.h"

namespace Xylena {
    
    void Scriptable::initialise() {
        //LuaHandler::registerItem(script, "", nullptr);
    }
    
    void Scriptable::callScriptFunction(SelectorPtr selector) {
        if (script) {
            (*selector)();
        }
    }
    
    SelectorPtr Scriptable::getSelector(std::string selector) {
        return SelectorPtr(new Selector((*script->getState())[selector.c_str()]));
    }
    
}