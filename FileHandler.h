#pragma once

//System includes
#include <string>

namespace Xylena {
    
    class FileHandler {
    public:
        static std::string readTextFile(std::string filename);
        static bool writeTextToFile(std::string filename, std::string content);
        static bool appendTextToFile(std::string filename, std::string content);
        
        
    };
}