#include "stdafx.h"
#include "ShaderHandler.h"

//System includes
#include <iostream>
#include <fstream>
#include <vector>
#include <map>

namespace Xylena {

    std::string ShaderHandler::readShaderFile(const char* filename) {
        
        std::string shaderSource;
        std::ifstream shaderReadStream(filename, std::ios::in);

        if (shaderReadStream.is_open()) {

            std::string line = "";
            while (getline(shaderReadStream, line)) {
                shaderSource += "\n" + line;
            }

            shaderReadStream.close();
        }

        return shaderSource;
    }

    VertexShader ShaderHandler::compileVertexShader(std::string source) {
        
        VertexShader shader = glCreateShader(GL_VERTEX_SHADER);
        int status = compileShader(source, shader);

        if (status == 0) {
            glDeleteShader(shader);
            return NULL;
        } else {
            return shader;
        }
    }

    FragmentShader ShaderHandler::compileFragmentShader(std::string source) {

        FragmentShader shader = glCreateShader(GL_FRAGMENT_SHADER);
        int status = compileShader(source, shader);

        if (status == 0) {
            glDeleteShader(shader);
            return NULL;
        } else {
            return shader;
        }
    }

    VertexShader ShaderHandler::createVertexShader(const char * filename) {
        return compileVertexShader(readShaderFile(filename));
    }

    FragmentShader ShaderHandler::createFragmentShader(const char * filename) {
        return compileFragmentShader(readShaderFile(filename));
    }

    int ShaderHandler::compileShader(std::string source, GLuint shader) {

        const char* shaderSourceString = source.c_str();

        glShaderSource(shader, 1, &shaderSourceString, NULL);
        glCompileShader(shader);

        GLint status;
        int infoLogLength = 0;

        glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);

        if (infoLogLength > 0) {
            std::vector<char> shaderErrorMessage(infoLogLength + 1);
            glGetShaderInfoLog(shader, infoLogLength, NULL, &shaderErrorMessage[0]);
            printf("%s\n", &shaderErrorMessage[0]);

        }

        if (status == GL_FALSE) {
            throw std::runtime_error("Unable to compile shader");
        } else {
            return 1;
        }

    }

    static std::map<ShaderProgram, std::vector<Shader>> programShaders;
    static std::map<std::string, ShaderProgram> programMap;

    ShaderProgram ShaderHandler::createProgram() {

        ShaderProgram program = glCreateProgram();
        return program;

    }

    void ShaderHandler::attachShader(ShaderProgram program, Shader shader) {
        
        glAttachShader(program, shader);

        auto it = programShaders.find(program);
        
        if (it == programShaders.end()) {
            std::vector<Shader> shaders;
            shaders.push_back(shader);
            programShaders.insert(std::pair<ShaderProgram, std::vector<Shader>>(program, shaders));
        } else {
            std::vector<Shader> shaders = programShaders[program];
            shaders.push_back(shader);
        }
    }

    ShaderProgram ShaderHandler::linkProgram(ShaderProgram program, std::string key) {
        
        glLinkProgram(program);

        GLint status;
        int infoLogLength;
        bool fail = false;

        glGetProgramiv(program, GL_LINK_STATUS, &status);
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLogLength);

        if (infoLogLength > 0) {
            std::vector<char> programErrorMessage(infoLogLength + 1);
            glGetProgramInfoLog(program, infoLogLength, NULL, &programErrorMessage[0]);
            printf("%s\n", &programErrorMessage[0]);
            fail = true;
        }

        auto it = programShaders.find(program);

        if (it != programShaders.end()) {
            std::vector<Shader> shaders = programShaders[program];
            
            for (unsigned int i = 0; i < shaders.size(); i++) {
                //glDetachShader(program, shaders[i]);
                glDeleteShader(shaders[i]);
            }

            programShaders.erase(program);
        } else {
            throw std::runtime_error("No available program");
        }

        if (fail) {
            throw std::runtime_error("Error linking shader program"); 
        } else {

            programMap.insert(std::pair<std::string, ShaderProgram>(key, program));
            return program;
        }

    }

    ShaderProgram ShaderHandler::getProgram(std::string key) {
        auto it = programMap.find(key);

        if (it != programMap.end()) {
            return programMap.at(key);
        } else {
            throw std::runtime_error("No such program: " + key);
        }
    }

    ShaderProgram ShaderHandler::createProgram(const char * programName, const char * vertexName, const char * fragmentName) {
        
        ShaderProgram program = createProgram();

        VertexShader vertexShader = ShaderHandler::createVertexShader(vertexName);
        FragmentShader fragmentShader = ShaderHandler::createFragmentShader(fragmentName);

        ShaderHandler::attachShader(program, vertexShader);
        ShaderHandler::attachShader(program, fragmentShader);

        return ShaderHandler::linkProgram(program, programName);

    }
    
    ShaderProgram ShaderHandler::compileProgram(const char * programName, const char * vertexSource, const char * fragmentSource) {
        
        ShaderProgram program = createProgram();
        
        VertexShader vertexShader = ShaderHandler::compileVertexShader(vertexSource);
        FragmentShader fragmentShader = ShaderHandler::compileFragmentShader(fragmentSource);
        
        ShaderHandler::attachShader(program, vertexShader);
        ShaderHandler::attachShader(program, fragmentShader);
        
        return ShaderHandler::linkProgram(program, programName);
        
    }

    ShaderAttribute ShaderHandler::getAttribute(ShaderProgram program, const char * attributeName) {
        
        if (!attributeName) {
            throw std::runtime_error("Attribute name was NULL");
        }

        ShaderAttribute attribute = glGetAttribLocation(program, attributeName);

        if (attribute == -1) {
            throw std::runtime_error(std::string("Attribute not found: ") + attributeName);
        }

        return attribute;
    }

    ShaderUniform ShaderHandler::getUniform(ShaderProgram program, const char * uniformName) {
        
        if (!uniformName) {
            throw std::runtime_error("Uniform name was NULL");
        }

        ShaderUniform uniform = glGetUniformLocation(program, uniformName);

        if (uniform == -1) {
            throw std::runtime_error(std::string("Uniform not found: ") + uniformName);
        }

        return uniform;
    }
}