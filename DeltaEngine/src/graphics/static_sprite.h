#pragma once
#include "renderable_2d.h"

namespace delta
{
	namespace graphics
	{
		class StaticSprite : public Renderable2D
		{
			Shader& shader_;
			VertexArray* vao_;
			IndexBuffer* ibo_;
		public:

			StaticSprite(math::vec3 position, math::vec2 size, math::vec4 color, Shader& shader);
			~StaticSprite();

			inline const Shader& getShader() const { return shader_; }
			inline const VertexArray* getVao() const { return vao_; }
			inline const IndexBuffer* getIbo() const { return ibo_; }
		};
	}
}