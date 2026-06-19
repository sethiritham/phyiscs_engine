#shader vertex
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

out vec3 ourColor;

uniform mat4 u_model_matrix;
uniform mat4 u_projection_matrix;

uniform float u_aspect_ratio;

void main()
{
    gl_Position = u_projection_matrix * u_model_matrix * vec4(aPos.x, aPos.y, aPos.z, 1.0f);
    ourColor = aColor;
}

#shader fragment
#version 330 core

out vec4 FragColor;

in vec3 ourColor;

void main()
{
    FragColor = vec4(ourColor.x, ourColor.y, ourColor.z, 1.0f);
}
