#version 330 core

layout (location = 0) in vec3 position_in;
layout (location = 2) in vec2 texture_coordinate_in;
layout (location = 3) in float texture_slot_in;
layout (location = 4) in vec4 color_in;

out DATA
{
	vec4 color;
	vec2 texture_coordinate;
	float texture_slot;
} vs_out;

uniform mat4 proj;
uniform mat4 view = mat4(1.0f);
uniform mat4 model = mat4(1.0f);

void main()
{
	vs_out.color = color_in;
	vs_out.texture_coordinate = texture_coordinate_in;
	vs_out.texture_slot = texture_slot_in;
	
	gl_Position = proj * view * model * vec4(position_in, 1.0f);
}