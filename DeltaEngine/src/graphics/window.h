#pragma once
#include <iostream>
#include <GL\glew.h>
#include <GLFW/glfw3.h>
#include "../math/math.h"

#define MAX_KEYS	500
#define MAX_BUTTONS	32

namespace delta
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
			math::vec2 getMousePosition() const;
		private:

			// you should not make your friend functions static member functions of the class 
			// because GLFW expects C-style function pointers (not member functions).
			friend void windowSizeCallback(GLFWwindow* window, int width, int height);
			friend void frameBufferSizeCallback(GLFWwindow* window, int width, int height);
			friend void keyCallback(GLFWwindow* window, int key_code, int scan_code, int action, int mods);
			friend void mousePositionCallback(GLFWwindow* window, double x_position, double y_position);
			friend void mouseButtonCallback(GLFWwindow* window, int button_code, int action, int mods);
		};
	}
}