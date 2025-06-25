#include "layer.h"

namespace delta
{
	namespace graphics
	{
		Layer::Layer(Renderer2D* renderer, Shader* shader, math::mat4 projection_matrix_)
			: renderer_(renderer), shader_(shader), projection_matrix_(projection_matrix_)
		{
			shader_->enable();
			shader_->setMat4f("proj", false, projection_matrix_);
		}

		Layer::~Layer()
		{
			delete renderer_;
			delete shader_;
			for (int i = 0; i < objects_.size(); i++)
				delete objects_[i];
		}

		void Layer::add(Renderable2D* object)
		{
			objects_.push_back(object);
		}

		void Layer::render()
		{
			shader_->enable();
			renderer_->begin();
			for (int i = 0; i < objects_.size(); i++)
				objects_[i]->submit(renderer_);
			renderer_->end();
			renderer_->flush();
		}
	}
}