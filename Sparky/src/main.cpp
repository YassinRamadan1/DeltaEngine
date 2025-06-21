#include "graphics/window.h"

int main()
{
	glfwWindowHint(GLFW_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	Sparky::graphics::Window window("test", 800, 600);
	glClearColor(1.0f, 0.0f, 0.0f, 1.0f);

	Log(glGetString(GL_VERSION));
	Log('\n');
	
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