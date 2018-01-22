#version 330 core

in vec3 worldspacePosition;
in vec2 vertexUV;

out vec2 UV;

uniform mat4 positioner;

void main() {
	gl_Position = positioner * vec4(worldspacePosition, 1);
	UV = vertexUV;
}