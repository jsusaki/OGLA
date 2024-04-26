#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texcoords;
layout (location = 3) in vec4 color;
layout (location = 4) in vec3 tangent;
layout (location = 5) in vec3 bitangent;

out vec3 FragPos;
out vec3 Normal;
out vec2 TexCoords;
out vec4 Color;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    FragPos   = vec3(model * vec4(position, 1.0));
    Normal    = mat3(transpose(inverse(model))) * normal;  
    TexCoords = texcoords;
    Color     = color;

    gl_Position = projection * view * vec4(FragPos, 1.0);
}