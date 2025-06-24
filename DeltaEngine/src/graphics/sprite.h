#pragma once
#include "renderable_2d.h"

namespace delta
{
	namespace graphics
	{
		class Sprite : public Renderable2D
		{
		public:
			Sprite(math::vec3 position, math::vec2 size, math::vec4 color);
		};
	}
}