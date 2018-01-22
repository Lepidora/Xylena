#pragma once

//System includes
#include <memory>

//Library includes
#include <selene.h>

//Local includes
#include "State.h"

namespace Xylena {
    
    using namespace sel;
    
    class Script {
    protected:
        StatePtr state;
    public:
        
        Script(std::string filename);
        
        StatePtr getState();
        
        template<typename O, typename... Fs>
        void addObject(std::string name, O& object, Fs&... functions) {
            (*state)[name.c_str()].SetObj(object, functions...);
        }
        
        template<typename I>
        void registerItem(std::string itemName, I item) {
            (*state)[itemName.c_str()] = item;
        }
        
    };
    
    //Typedefs
    typedef std::shared_ptr<Script> ScriptPtr;
}