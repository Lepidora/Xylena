#pragma once

//System includes
#include <unordered_map>

//Library includes
#include <selene.h>

namespace Xylena {
    
    using namespace sel;
    
    class LuaHandler {
    private:
        static std::unordered_map<std::string, std::string *> filemap;
        
        std::string * loadThroughCache(std::string filename);
    public:
        
        void reloadScripts();
        
        State loadFile(std::string filename, bool libs);
        
        template<typename O, typename... Fs>
        void addObject(State state, std::string name, O object, Fs... functions);
        
        template<typename I>
        void registerItem(State state, std::string itemName, I item);
    };
}