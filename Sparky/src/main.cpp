#include "graphics/window.h"
#include "math/math.h"
#include "graphics/shader.h"

#ifdef DEBUG
#define Log(x) std::cout << (x)

#else
#define Log(x)

#endif

int main()
{
	//glfwWindowHint(GLFW_VERSION_MAJOR, 3);
	//glfwWindowHint(GLFW_VERSION_MINOR, 3);
	//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	using namespace sparky;
	using namespace graphics;
	using namespace math;

	Window window("test", 800, 600);
	glClearColor(0.2f, 0.3f, 0.5f, 1.0f);

	Log(glGetString(GL_VERSION));
	Log('\n');

	GLfloat vertices[] =
	{
		1.0f, 0.0f, 
		-1.0f, 0.0f,
		0.0f, 1.0f
	};

	Shader triangle_shader("res/shaders/triangle.vert", "res/shaders/triangle.frag");
	unsigned int vao, vbo;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)(0));
	glEnableVertexAttribArray(0);

	while (!window.isClosed())
	{
		window.clear();

		if (window.isKeyPressed(GLFW_KEY_ESCAPE))
			window.close();


		triangle_shader.enable();
		triangle_shader.set4f("color", vec4(1.0f));
		glDrawArrays(GL_TRIANGLES, 0, 3);
		window.update();
	}

	return 0;
}