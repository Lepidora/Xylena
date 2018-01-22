#pragma once

//System includes
#include <unordered_map>

//Library includes
#include <selene.h>

//Local includes
#include "State.h"

namespace Xylena {
    
    using namespace sel;
    
    class LuaHandler {
    private:
        static std::unordered_map<std::string, std::string *> filemap;
        
        static std::string * loadThroughCache(std::string filename);
    public:
        
        static void reloadScripts();
        
        static StatePtr loadFile(std::string filename, bool libs);
        
        static StatePtr getNewState();
        static StatePtr getNewState(lua_State *luaState);
    };
}