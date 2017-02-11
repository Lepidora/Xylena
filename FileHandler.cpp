#include "FileHandler.h"

#include <iostream>
#include <fstream>
#include <sstream>

namespace Xylena {
    
    std::string FileHandler::readTextFile(std::string filename) {
        
        std::ifstream file(filename);
        
        if (file.is_open()) {
            std::stringstream stream;
            stream << file.rdbuf();
            return stream.str();
        } else {
            return nullptr;
        }
    }
    
    bool FileHandler::writeTextToFile(std::string filename, std::string content) {
        
        std::ofstream file(filename);
        
        if (file.is_open()) {
            file << content;
            return true;
        } else {
            return false;
        }
    }
    
    bool FileHandler::appendTextToFile(std::string filename, std::string content) {
        
        std::ofstream file(filename, std::ios_base::app);
        
        if (file.is_open()) {
            file << content;
            return true;
        } else {
            return false;
        }
    }
    
}