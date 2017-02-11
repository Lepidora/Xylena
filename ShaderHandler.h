#pragma once

//System includes
#include <string>

//Local includes
#include "GLTypes.h"

namespace Xylena {

    class ShaderHandler {
    private:
        static int compileShader(std::string source, GLuint shader);

        ///Generic file reading method
        static std::string readShaderFile(const char* filename);

        ///Compile Vertex/Fragment shaders from source
        static VertexShader compileVertexShader(std::string source);
        static FragmentShader compileFragmentShader(std::string source);

    public:
        ShaderHandler() {};
        ~ShaderHandler() {};

        ///Create vertex/fragment shaders from filename
        static VertexShader createVertexShader(const char* filename);
        static FragmentShader createFragmentShader(const char* filename);

        ///Create shader program
        static ShaderProgram createProgram();

        ///Bind vertex/fragment shader to program
        static void attachShader(ShaderProgram program, Shader shader);

        ///Link shaders and create program
        static ShaderProgram linkProgram(ShaderProgram program, std::string key);

        ///Gets shader program from the mapping
        static ShaderProgram getProgram(std::string key);

        ///All-in-one shader creation method
        static ShaderProgram createProgram(const char* programName, const char* vertexName, const char* fragmentName);
        
        ///All-in-one shader creation method where the source has is already known
        static ShaderProgram compileProgram(const char * programName, const char * vertexSource, const char * fragmentSource);

        ///Get attribute from shader program
        static ShaderAttribute getAttribute(ShaderProgram program, const char* attributeName);

        ///Get uniform for shader program
        static ShaderUniform getUniform(ShaderProgram program, const char* uniformName);
    };
}
