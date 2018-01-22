#pragma once

//System includes
#include <string>

//Library includes
#include <selene.h>

//Local includes
#include "Script.h"
#include "Selector.h"

namespace Xylena {
    
    using namespace sel;
    
    class Scriptable {
    protected:
        ScriptPtr script;
        
        virtual void initialise();
    public:
        
        ///It's recommended you overload this and cache any selectors used
        virtual void callScriptFunction(SelectorPtr selector);
        
        virtual SelectorPtr getSelector(std::string selector);
    };
}