#pragma once
#include "../renderer_2d.h"
#include "../shader.h"
#include "../renderable_2d.h"

namespace delta
{
	namespace graphics
	{
		class Layer
		{
		protected:

			std::vector<Renderable2D*> objects_;
			Renderer2D* renderer_;
			Shader* shader_;
			math::mat4 projection_matrix_;
			
			Layer(Renderer2D* renderer_, Shader* shader_, math::mat4 projection_matrix_);
		public:

			virtual ~Layer();

			void add(Renderable2D* object);
			void render();
			inline void setProjectionMatrix(math::mat4 projection_matrix)
			{
				projection_matrix_ = projection_matrix;
				shader_->enable();
				shader_->setMat4f("proj", false, projection_matrix_);
			}
		};
	}
}