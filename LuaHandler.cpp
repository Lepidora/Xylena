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
    
    StatePtr LuaHandler::loadFile(std::string filename, bool libs) {
        
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
        
        StatePtr state = getNewState(luaState);
        return state;
    }
    
    StatePtr LuaHandler::getNewState() {
        return StatePtr(new State(true));
    }
    
    StatePtr LuaHandler::getNewState(lua_State *luaState) {
        return StatePtr(new State(luaState));
    }
    
    
}