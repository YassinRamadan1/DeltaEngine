#pragma once

#include "buffers/vertex_buffer.h"
#include "buffers/index_buffer.h"
#include "buffers/vertex_array.h"
#include "../math/math.h"
#include "shader.h"
#include "renderer_2d.h"
#include "texture.h"

namespace delta
{
	namespace graphics
	{
		struct Vertex
		{
			math::vec3 position_;
			unsigned int color_;
			math::vec2 texture_coordinate_;
			float texture_slot_;
		};

		class Renderable2D
		{
		protected:

			Texture* texture_;
			math::vec2 size_;
			math::vec3 position_;
			math::vec4 color_;
			std::vector<math::vec2> texture_coordinates_ =
			{
				math::vec2(0.0, 0.0),
				math::vec2(1.0, 0.0),
				math::vec2(1.0, 1.0),
				math::vec2(0.0, 1.0)
			};

			Renderable2D() { }
			Renderable2D(math::vec3 position, math::vec2 size, math::vec4 color, Texture* texture)
				: size_(size), position_(position), color_(color), texture_(texture) { }
		public:

			virtual ~Renderable2D() = default;
			virtual void submit(Renderer2D* renderer) 
			{
				renderer->submit(this);
			}

			inline const math::vec2& getSize() const { return size_; }
			inline const math::vec3& getPosition() const { return position_; }
			inline const math::vec4& getColor() const { return color_; }
			inline const std::vector<math::vec2>& getTextureCoordinates() const { return texture_coordinates_; }
			inline void setTextureCoordinates(const std::vector<math::vec2>& uvs) { texture_coordinates_ = uvs; }
			inline const unsigned int& getTextureID() const { return ((texture_) ? texture_->getID() : 0); }
		};
	}
}