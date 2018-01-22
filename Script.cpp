#include "Script.h"

//Local includes
#include "LuaHandler.h"

namespace Xylena {
    
    
    /*template<typename O, typename... Fs>
    void Script::addObject(std::string name, O& object, Fs&... functions) {
        (*state)[name.c_str()].SetObj(object, functions...);
    }*/
    
    Script::Script(std::string filename) {
        state = LuaHandler::loadFile(filename, true);
    }
    
    StatePtr Script::getState() {
        return state;
    }
    
}