#include "graphics/window.h"
#include "math/math.h"

int main()
{
	//glfwWindowHint(GLFW_VERSION_MAJOR, 3);
	//glfwWindowHint(GLFW_VERSION_MINOR, 3);
	//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	using namespace Sparky;
	using namespace graphics;
	using namespace math;

	Window window("test", 800, 600);
	glClearColor(1.0f, 1.0f, 0.0f, 1.0f);

	Log(glGetString(GL_VERSION));
	Log('\n');
	
	
	vec2 a(1.0f), b(2.0, 3.0), c;
	c = a + b;
	c = normalize(c);
	vec4 x(1.0f, 2.0f, 3.0f, 1.0f);
	mat4 mat(vec4(1.0, 0.0, 0.0, 0.0), vec4(0.0, 1.0, 0.0, 0.0), vec4(0.0, 0.0, 1.0, 0.0), vec4(1.0, 1.0, 1.0, 1.0));
	x = mat * x;
	std::cout << x;

	Log(c);
	unsigned int vao, vbo;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	while (!window.isClosed())
	{
		window.clear();

		if (window.isKeyPressed(GLFW_KEY_ESCAPE))
			window.close();
		glDrawArrays(GL_TRIANGLES, 0, 6);
		window.update();
	}

	return 0;
}