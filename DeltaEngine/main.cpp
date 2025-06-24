#include "src/graphics/window.h"
#include "src/math/math.h"
#include "src/graphics/shader.h"
#include "src/graphics/static_sprite.h"
#include "src/graphics/sprite.h"
#include "src/graphics/simple_renderer_2d.h"
#include "src/graphics/batch_renderer_2D.h"
#include "src/utils/timer.h"

#include <time.h>

#ifdef DEBUG
#define Log(x) std::cout << (x)

#else
#define Log(x)

#endif

#define BATCH 1

int main()
{
	//glfwWindowHint(GLFW_VERSION_MAJOR, 3);
	//glfwWindowHint(GLFW_VERSION_MINOR, 3);
	//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	using namespace delta;
	using namespace graphics;
	using namespace math;

	Window window("test", 800, 600);
	glClearColor(0.2f, 0.3f, 0.5f, 1.0f);

	Log(glGetString(GL_VERSION));
	Log('\n');
	Timer timer;
	mat4 ortho = orthographic(0, 16, 0, 9, -1, 1);

	Shader triangle_shader("res/shaders/triangle.vert", "res/shaders/triangle.frag");
	triangle_shader.enable();
	triangle_shader.setMat4f("proj", false, ortho);
	
	srand(time(0));
	std::vector<Renderable2D*> sprites;
#if BATCH
	BatchRenderer2D renderer;
#else
	SimpleRenderer2D renderer;
#endif

	for(float x = 0; x < 16.0; x += 0.05)
		for (float y = 0; y < 9; y += 0.05)
		{
			sprites.push_back(new
#if BATCH
				Sprite
#else
				StaticSprite
#endif
				(vec3(x, y, 0), vec2(0.04, 0.04), vec4(rand() % 1000 / 1000.0, rand() % 1000 / 1000.0, rand() % 1000 / 1000.0, 1)
#if !BATCH		
					, triangle_shader
#endif
					));
		}
	
	Timer time;
	int count = 0;
	while (!window.isClosed())
	{
		count++;
		window.clear();

		if (window.isKeyPressed(GLFW_KEY_ESCAPE))
			window.close();

		timer.reset();
#if BATCH
		renderer.begin();
#endif
		//for(int i = 0; i< sprites.size(); i++)
			renderer.submit(sprites);
#if BATCH
		renderer.end();
#endif
		renderer.flush();
		window.update();
		if (time.elapsed() > 1.0f)
		{
			printf("%d fps\n", count);
			count = 0;
			time.reset();
		}
		//printf("%f ms\n", timer.elapsed());
	}

	return 0;
}