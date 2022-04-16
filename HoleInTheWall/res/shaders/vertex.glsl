#version 330 core
layout (location = 0) in vec4 vertex;

// vertex.x : position x axis
// vertex.y : position y axis

// vertex.z : texture x axis
// vertex.w : texture y axis

out vec2 TexturePosition;

uniform mat4 projection;
uniform mat4 model;

void main()
{
    TexturePosition = vertex.zw;
    gl_Position = projection * model * vec4(vertex.xy, 0.0f, 1.0f);
}