#include "simple_renderer_2d.h"
#include "renderable_2d.h"

namespace delta
{
	namespace graphics
	{
		void SimpleRenderer2D::submit(Renderable2D* object)
		{
			render_queue_.push_back(object);
		}

		void SimpleRenderer2D::submit(const std::vector<Renderable2D*>& objects)
		{
			//render_queue_.insert(render_queue_.end(), objects.begin(), objects.end());
			for (int i = 0; i < objects.size(); i++)
				render_queue_.push_back(objects[i]);
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