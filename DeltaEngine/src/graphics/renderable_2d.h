#pragma once

#include "buffers/vertex_buffer.h"
#include "buffers/index_buffer.h"
#include "buffers/vertex_array.h"
#include "../math/math.h"
#include "shader.h"
#include "renderer_2d.h"

namespace delta
{
	namespace graphics
	{
		struct Vertex
		{
			math::vec3 position_;
			unsigned int color_;
		};

		class Renderable2D
		{
		protected:

			math::vec2 size_;
			math::vec3 position_;
			math::vec4 color_;
		protected:

			Renderable2D() { }
		public:

			Renderable2D(math::vec3 position, math::vec2 size, math::vec4 color) 
				: size_(size), position_(position), color_(color)
			{ }

			virtual ~Renderable2D() = default;
			virtual void submit(Renderer2D* renderer) 
			{
				renderer->submit(this);
			}

			inline const math::vec2& getSize() const { return size_; }
			inline const math::vec3& getPosition() const { return position_; }
			inline const math::vec4& getColor() const { return color_; }
		};
	}
}