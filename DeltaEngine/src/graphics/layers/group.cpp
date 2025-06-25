#include "group.h"

namespace delta
{
	namespace graphics
	{
		Group::Group(math::mat4 model_matrix)
		: model_matrix_(model_matrix)
		{ }

		void Group::add(Renderable2D* object)
		{
			objects_.push_back(object);
		}

		void Group::submit(Renderer2D* renderer)
		{
			renderer->pushMatrix(model_matrix_);
			for (int i = 0; i < objects_.size(); i++)
				objects_[i]->submit(renderer);
			
			renderer->popMatrix();
		}
	}
}