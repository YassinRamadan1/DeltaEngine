#include "src/graphics/window.h"
#include "src/math/math.h"
#include "src/graphics/shader.h"
#include "src/graphics/static_sprite.h"
#include "src/graphics/sprite.h"
#include "src/graphics/simple_renderer_2d.h"
#include "src/graphics/batch_renderer_2D.h"
#include "src/utils/timer.h"
#include "src/graphics/layers/tile_layer.h"
#include "src/graphics/layers/group.h"

#ifdef DEBUG
#define Log(x) std::cout << (x)

#else
#define Log(x)

#endif

#define BATCH 1

void manySprites()
{
	using namespace delta;
	using namespace graphics;
	using namespace math;

	Window window("sprites", 800, 600);
	glClearColor(0.2f, 0.3f, 0.5f, 1.0f);

	Log(glGetString(GL_VERSION));
	Log('\n');
	mat4 ortho = orthographic(-20, 20, -15, 15, -1, 1);

	Shader* s = new Shader("res/shaders/triangle.vert", "res/shaders/triangle.frag");
	Shader& triangle_shader = *s;

	TileLayer* layer = new TileLayer(s, ortho);

	srand(time(0));
	std::vector<Renderable2D*> sprites;
	for (float x = 0; x < 16.0; x += 0.05)
		for (float y = 0; y < 9; y += 0.05)
		{
			sprites.push_back(new Sprite(vec3(x, y, 0), vec2(0.04, 0.04), vec4(rand() % 1000 / 1000.0, rand() % 1000 / 1000.0, rand() % 1000 / 1000.0, 1)));
		}
	for (int i = 0; i < sprites.size(); i++)
		layer->add(sprites[i]);

	Timer timer, time;
	int count = 0;
	while (!window.isClosed())
	{
		timer.reset();
		count++;

		window.clear();

		if (window.isKeyPressed(GLFW_KEY_ESCAPE))
			window.close();

		layer->render();

		window.update();
		if (time.elapsed() > 1.0f)
		{
			printf("%d fps\n", count);
			count = 0;
			time.reset();
		}

		//printf("%f ms\n", timer.elapsed());
	}

	delete layer;
}

void hierarchy()
{
	using namespace delta;
	using namespace graphics;
	using namespace math;

	Window window("hierarchy", 800, 600);
	glClearColor(0.2f, 0.3f, 0.5f, 1.0f);

	Log(glGetString(GL_VERSION));
	Log('\n');
	mat4 ortho = orthographic(0, 16, 0, 9, -1, 1);

	Shader* s = new Shader("res/shaders/triangle.vert", "res/shaders/triangle.frag");
	Shader& triangle_shader = *s;

	TileLayer* layer = new TileLayer(s, ortho);
	Group* group = new Group(translate(vec3(1, 1, 0)));
	Group* group1 = new Group(translate(vec3(1, 1, 0)));

	group->add(new Sprite(vec3(0, 0, 0), vec2(8, 5), vec4(1.0f)));
	group1->add(new Sprite(vec3(0, 0, 0), vec2(2, 2), vec4(1.0f, 0, 0, 1.0f)));
	group->add(group1);

	layer->add(group);

	Timer timer, time;
	int count = 0;
	while (!window.isClosed())
	{
		timer.reset();
		count++;

		window.clear();

		if (window.isKeyPressed(GLFW_KEY_ESCAPE))
			window.close();

		layer->render();

		window.update();
		if (time.elapsed() > 1.0f)
		{
			printf("%d fps\n", count);
			count = 0;
			time.reset();
		}

		//printf("%f ms\n", timer.elapsed());
	}

	delete layer;
}

int main()
{
	hierarchy();
	return 0;
}