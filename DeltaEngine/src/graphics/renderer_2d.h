#pragma once

#include <GL/glew.h>
#include <iostream>
#include <vector>
#include <deque>
#include "../math/math.h"
#include "buffers/vertex_buffer.h"
#include "buffers/index_buffer.h"
#include "buffers/vertex_array.h"

namespace delta
{
	namespace graphics
	{
		class Renderable2D;
		struct Vertex;

		class Renderer2D
		{
		protected:

			std::vector<math::mat4> transformation_stack_;
			
			Renderer2D()
			{
				transformation_stack_.push_back(math::mat4(1.0f));
			}
		public:

			virtual ~Renderer2D() = default;

			void pushMatrix(const math::mat4& matrix, bool override = false)
			{
				if (override)
					transformation_stack_.push_back(matrix);
				else
					transformation_stack_.push_back(transformation_stack_.back() * matrix);
			}

			void popMatrix()
			{
				if (transformation_stack_.size() > 1)
					transformation_stack_.pop_back();
			}

			virtual void begin() { }
			virtual void submit(Renderable2D* object) = 0;
			virtual void end() { }
			virtual void flush() = 0;
		};
	}
}
