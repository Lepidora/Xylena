#include "LuaHandler.h"

//System includes
#include <string>

//Local includes
#include "FileHandler.h"

namespace Xylena {
    
    std::unordered_map<std::string, std::string *> LuaHandler::filemap;
    
    std::string * LuaHandler::loadThroughCache(std::string filename) {
        
        std::string *fileContents;
        std::unordered_map<std::string, std::string *>::iterator mapIt;;
        
        if ((mapIt = filemap.find(filename)) == filemap.end()) {
            std::string temp = FileHandler::readTextFile(filename);
            fileContents = new std::string(temp);
            
            filemap.insert(std::pair<std::string, std::string *>(filename, fileContents));
        } else {
            fileContents = mapIt->second;
        }
        
        return fileContents;
    }
    
    void LuaHandler::reloadScripts() {
        filemap.clear();
    }
    
    State LuaHandler::loadFile(std::string filename, bool libs) {
        
        lua_State *luaState = luaL_newstate();
        
        if (libs) {
            luaL_openlibs(luaState);
        }
        
        std::string script = *loadThroughCache(filename);
        
        int status = luaL_loadstring(luaState, script.c_str());
        
        if (status) {
            std::cout << "Error loading script " << filename << ":" << lua_tostring(luaState, -1);
            return nullptr;
        }
        
        status = lua_pcall(luaState, 0, LUA_MULTRET, 0);
        
        if (status) {
            std::cout << "Error loading script " << filename << ":" << lua_tostring(luaState, -1);
            return nullptr;
        }
        
        State state(luaState);
        return state;
    }
    
    template<typename O, typename... Fs>
    void LuaHandler::addObject(State state, std::string name, O object, Fs... functions) {
        state[name.c_str()].SetObj(object, functions...);
    }
    
    template<typename I>
    void LuaHandler::registerItem(sel::State state, std::string name, I item) {
        state[name.c_str()] = item;
    }
    
}