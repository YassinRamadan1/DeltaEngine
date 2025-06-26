#include "sprite.h"

namespace delta
{
	namespace graphics
	{
		Sprite::Sprite(math::vec3 position, math::vec2 size, math::vec4 color)
			: Renderable2D(position, size, color, nullptr)
		{ }

		Sprite::Sprite(math::vec3 position, math::vec2 size, Texture* texture)
			: Renderable2D(position, size, math::vec4(0.0f), texture)
		{ }

	}
}