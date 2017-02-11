#ifndef __DEFAULT_SHADERS__

#define __DEFAULT_SHADERS__

const char * const defaultSimpleVert = ""
""
"#version 330 core                                      \n"
""
"layout(location = 0) in vec3 vertexPosition_modelspace;\n"
""
"void main() {                                          \n"
"    gl_Position.xyz = vertexPosition_modelspace;       \n"
"    gl_Position.w = 1.0;                               \n"
"}";

const char * const defaultSimpleFrag = ""
""
"#version 330 core          \n"
""
"out vec3 color;            \n"
""
"void main() {              \n"
"    color = vec3(1, 0, 0); \n"
"}";


const char * const defaultTextureVert = ""
""
"#version 330 core                                          \n"
""
"in vec3 worldspacePosition;                                \n"
"in vec2 vertexUV;                                          \n"
""
"out vec2 UV;                                               \n"
""
"uniform mat4 positioner;                                   \n"
""
"void main() {                                              \n"
"    gl_Position = positioner * vec4(worldspacePosition, 1);\n"
"    UV = vertexUV;                                         \n"
"}";

const char * const defaultTextureFrag = ""
""
"#version 330 core                          \n"
""
"in vec2 UV;                                \n"
""
"out vec4 color;                            \n"
""
"uniform sampler2D textureSampler;          \n"
""
"void main() {                              \n"
"    color = texture(textureSampler, UV);   \n"
"}";

#endif