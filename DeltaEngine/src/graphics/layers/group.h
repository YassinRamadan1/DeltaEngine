#pragma once
#include "../renderable_2d.h"
#include <iostream>

namespace delta
{
	namespace graphics
	{
		class Group : public Renderable2D
		{

			std::vector<Renderable2D*> objects_;
			math::mat4 model_matrix_;
		public:

			Group(math::mat4 model_matrix);
			
			void add(Renderable2D* object);
			void submit(Renderer2D* renderer) override;
			inline void setTransformationMatrix(math::mat4 matrix) { model_matrix_ = matrix; }
		};
	}
}