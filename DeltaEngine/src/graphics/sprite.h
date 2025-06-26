#pragma once
#include "renderable_2d.h"

namespace delta
{
	namespace graphics
	{
		class Sprite : public Renderable2D
		{
			std::vector<math::vec2> texture_coordinates_ = 
			{
				math::vec2(0.0, 0.0),
				math::vec2(1.0, 0.0),
				math::vec2(1.0, 1.0),
				math::vec2(0.0, 1.0)
			};
		public:

			Sprite(math::vec3 position, math::vec2 size, math::vec4 color);
			Sprite(math::vec3 position, math::vec2 size, Texture* texture = nullptr);
		};
	}
}