#version 330 core

in DATA
{
	vec4 color;
	vec2 texture_coordinate;
	float texture_slot;
} fs_in;

out vec4 fragment_color;

uniform sampler2D textures[32];

void main()
{
	int slot = int(fs_in.texture_slot + 0.5);
	
	if (slot == 0)
	{
		fragment_color = fs_in.color;
	}
	else
	{
		fragment_color = vec4(texture(textures[slot - 1], fs_in.texture_coordinate).rgb, 1.0f);
	}
}