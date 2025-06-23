#version 330 core

layout (location = 0) in vec3 position_in;
layout (location = 4) in vec4 color_in;

out vec4 color;

uniform mat4 proj;
uniform mat4 view = mat4(1.0f);
uniform mat4 model = mat4(1.0f);

void main()
{
	color = color_in;
	gl_Position = proj * view * model * vec4(position_in, 1.0f);
}
