#include "simple_renderer_2d.h"

namespace sparky
{
	namespace graphics
	{
		void SimpleRenderer2D::submit(Renderable2D* object)
		{
			render_queue_.push_back(object);
		}

		void SimpleRenderer2D::flush()
		{
			while (!render_queue_.empty())
			{
				StaticSprite* object = (StaticSprite*)render_queue_.front();
				
				object->getVao()->bind();
				object->getIbo()->bind();
				object->getShader().enable();
				object->getShader().setMat4f("model", false, math::translate(object->getPosition()));
				glDrawElements(GL_TRIANGLES, object->getIbo()->getCount(), GL_UNSIGNED_INT, nullptr);
				object->getVao()->unbind();
				object->getIbo()->unbind();
				render_queue_.pop_front();
			}
		}
	}
}