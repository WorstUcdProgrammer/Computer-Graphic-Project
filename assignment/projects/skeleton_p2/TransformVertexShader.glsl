#version 330 core

layout(location = 0) in vec3 vertexPosition_modelspace;

uniform mat4 Matrix;
uniform mat4 transMatrix;
uniform mat4 rotateMatrix;
uniform int render;

void main() {
    if (render == 1)
    {
        gl_Position = ((vec4(vertexPosition_modelspace, 1) * transMatrix) * rotateMatrix) * Matrix;
    } else {
        gl_Position = vec4(vertexPosition_modelspace, 1);
    }
}
