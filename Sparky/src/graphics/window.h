#pragma once
#include <iostream>
#include <GL\glew.h>
#include <GLFW/glfw3.h>

#define MAX_KEYS	500
#define MAX_BUTTONS	32

namespace sparky
{
	namespace graphics
	{
		class Window
		{
			int width_, height_;
			const char* window_title_;
			GLFWwindow* window_;
			bool keyboard_keys_[MAX_KEYS];
			bool mouse_buttons_[MAX_BUTTONS];
			double mouse_x_position_, mouse_y_position_;
		public:

			Window(const char* window_title, int width, int height);
			~Window();
			void close() const;
			bool isClosed() const;
			void clear() const;
			void update() const;
			inline int getWidth() const { return width_; }
			inline int getHeight() const { return height_; }
			bool isKeyPressed(int key_code) const;
			bool isButtonPressed(int button_code) const;
		private:

			// you should not make your friend functions static member functions of the class 
			// because GLFW expects C-style function pointers (not member functions).
			friend static void windowSizeCallback(GLFWwindow* window, int width, int height);
			friend static void frameBufferSizeCallback(GLFWwindow* window, int width, int height);
			friend static void keyCallback(GLFWwindow* window, int key_code, int scan_code, int action, int mods);
			friend static void mousePositionCallback(GLFWwindow* window, double x_position, double y_position);
			friend static void mouseButtonCallback(GLFWwindow* window, int button_code, int action, int mods);
		};
	}
}