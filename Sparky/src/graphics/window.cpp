#include "window.h"

#ifdef DEBUG
#define Log(x) std::cout << (x)

#else
#define Log(x)

#endif

namespace sparky
{
	namespace graphics
	{
		void windowSizeCallback(GLFWwindow* window, int width, int height);
		void frameBufferSizeCallback(GLFWwindow* window, int width, int height);
		void keyCallback(GLFWwindow* window, int key_code, int scan_code, int action, int mods);
		void mousePositionCallback(GLFWwindow* window, double x_position, double y_position);
		void mouseButtonCallback(GLFWwindow* window, int button_code, int action, int mods);

		Window::Window(const char* window_title, int width, int height) : width_(width), height_(height)
		{
			window_title_ = window_title;
			
			if (!glfwInit())
			{
				Log("Failed to initialize glfw\n");
			}

			window_ = glfwCreateWindow(width_, height_, window_title_, nullptr, nullptr);
			if (!window_)
			{
				Log("Failed to create a window\n");
				glfwTerminate();
			}

			glfwMakeContextCurrent(window_);
			
			glfwSetWindowUserPointer(window_, this);
			glfwSetFramebufferSizeCallback(window_, frameBufferSizeCallback);
			glfwSetWindowSizeCallback(window_, windowSizeCallback);
			glfwSetKeyCallback(window_, keyCallback);
			glfwSetCursorPosCallback(window_, mousePositionCallback);
			glfwSetMouseButtonCallback(window_, mouseButtonCallback);

			for (int i = 0; i < MAX_KEYS; i++)
			{
				keyboard_keys_[i] = false;
			}

			for (int i = 0; i < MAX_BUTTONS; i++)
			{
				keyboard_keys_[i] = false;
			}

			if (glewInit() != GLEW_OK)
			{
				Log("Failed to initialize glew\n");
			}
		}

		Window::~Window()
		{
			glfwDestroyWindow(window_);
		}
		
		void Window::close() const
		{
			glfwSetWindowShouldClose(window_, true);
		}

		bool Window::isClosed() const
		{
			return glfwWindowShouldClose(window_);
		}

		void Window::clear() const
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}

		void Window::update() const
		{
			glfwSwapBuffers(window_);
			glfwPollEvents();
		}

		bool Window::isKeyPressed(int key_code) const
		{
			return keyboard_keys_[key_code];
		}

		bool Window::isButtonPressed(int button_code) const
		{
			return mouse_buttons_[button_code];
		}

		void windowSizeCallback(GLFWwindow* window, int width, int height)
		{
			Window* win = (Window*)glfwGetWindowUserPointer(window);
			win->width_ = width;
			win->height_ = height;
		}

		void frameBufferSizeCallback(GLFWwindow* window, int width, int height)
		{
			glViewport(0, 0, width, height);
		}
		
		void keyCallback(GLFWwindow* window, int key_code, int scan_code, int action, int mods)
		{
			Window* win = (Window*)glfwGetWindowUserPointer(window);
			win->keyboard_keys_[key_code] = (action != GLFW_RELEASE);
		}

		void mousePositionCallback(GLFWwindow* window, double x_position, double y_position)
		{
			Window* win = (Window*)glfwGetWindowUserPointer(window);
			win->mouse_x_position_ = x_position;
			win->mouse_y_position_ = y_position;
		}

		void mouseButtonCallback(GLFWwindow* window, int button_code, int action, int mods)
		{
			Window* win = (Window*)glfwGetWindowUserPointer(window);
			win->mouse_buttons_[button_code] = (action != GLFW_RELEASE);
		}
	}
}