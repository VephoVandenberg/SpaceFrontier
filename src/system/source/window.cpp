#include <iostream>

#include "../include/window.h"

namespace GAME_NAMESPACE
{
	constexpr float width = 700.0f;
	constexpr float height = 800.0f;
	constexpr auto title = "SpaceFrontier";
	
	Window::Window(CallbackData& data) 
		: m_data(data)
	{
		init();
	}

	Window::~Window()
	{
		glfwDestroyWindow(m_window);
	}

	void Window::init()
	{
		if (!glfwInit())
		{
			std::cout << "Could not initialize GLFW" << std::endl;
			exit(EXIT_FAILURE);
		}

		m_window = glfwCreateWindow(width, height, title, nullptr, nullptr);
		glfwSetWindowUserPointer(m_window, &m_data);

		glfwSetWindowCloseCallback(
			m_window, 
			[](GLFWwindow* window) {
				auto data = *(CallbackData*)glfwGetWindowUserPointer(window);

				WindowCloseEvent event;

				data.func(event);
			});
	}

	void Window::update()
	{
		glfwPollEvents();
	}
}
