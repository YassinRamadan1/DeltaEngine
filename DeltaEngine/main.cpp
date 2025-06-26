#include "src/graphics/window.h"
#include "src/graphics/shader.h"
#include "src/math/math.h"
#include "src/utils/timer.h"

#include "src/graphics/static_sprite.h"
#include "src/graphics/sprite.h"
#include "src/graphics/simple_renderer_2d.h"
#include "src/graphics/batch_renderer_2D.h"
#include "src/graphics/layers/tile_layer.h"
#include "src/graphics/layers/group.h"
#include "src/graphics/texture.h"

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
	mat4 ortho = orthographic(0, 16, 0, 9, -1, 1);

	Shader* s = new Shader("res/shaders/texture.vert", "res/shaders/texture.frag");
	Shader& triangle_shader = *s;

	TileLayer* layer = new TileLayer(s, ortho);

	Texture texture_array[] = 
	{
		Texture("E:/Courses/CMU/Aiding.Videos/Assets/bricks2.jpg"),
		Texture("E:/Courses/CMU/Aiding.Videos/Assets/brickwall.jpg"),
		Texture("E:/Courses/CMU/Aiding.Videos/Assets/container.jpg"),
		Texture("E:/Courses/CMU/Aiding.Videos/Assets/container2.png"),
	};
	
	int data[] =
	{
		0, 1, 2, 3
	};

	triangle_shader.set1iv("textures", 4, data);

	srand(time(0));
	std::vector<Renderable2D*> sprites;
	int i = 0;
	for (float x = 0; x < 16.0; x += 1)
		for (float y = 0; y < 9; y += 1)
		{
			if(rand() % 2)
				sprites.push_back(new Sprite(vec3(x, y, 0), vec2(1, 1), vec4(rand() % 1000 / 1000.0, rand() % 1000 / 1000.0, rand() % 1000 / 1000.0, 1)));
			else
				sprites.push_back(new Sprite(vec3(x, y, 0), vec2(1, 1), &texture_array[(i++) % 4]));
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

	Shader* s = new Shader("res/shaders/texture.vert", "res/shaders/texture.frag");
	Shader& triangle_shader = *s;
	triangle_shader.enable();
	//triangle_shader

	Texture tex("E:/Courses/CMU/Aiding.Videos/Assets/bricks2.jpg");
	Texture tex1("E:/Courses/CMU/Aiding.Videos/Assets/brickwall.jpg");

	triangle_shader.set1i("textures[0]", 0);
	triangle_shader.set1i("textures[1]", 1);
	triangle_shader.set1i("textures[2]", 2);
	triangle_shader.set1i("textures[3]", 3);
	triangle_shader.set1i("textures[4]", 4);
	triangle_shader.set1i("textures[5]", 5);
	triangle_shader.set1i("textures[6]", 6);
	triangle_shader.set1i("textures[7]", 7);
	triangle_shader.set1i("textures[8]", 8);
	triangle_shader.set1i("textures[9]", 9);

	TileLayer* layer = new TileLayer(s, ortho);

	Group* group = new Group(translate(vec3(1, 1, 0)));
	Group* group1 = new Group(translate(vec3(1, 1, 0)));

	group->add(new Sprite(vec3(0, 0, 0), vec2(8, 5), &tex1));
	group1->add(new Sprite(vec3(0, 0, 0), vec2(2, 2), &tex));
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
	using namespace delta;
	using namespace graphics;
	using namespace math;

	manySprites();
	return 0;
}
