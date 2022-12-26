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
			glfwTerminate();
			exit(EXIT_FAILURE);
		}

		m_window = glfwCreateWindow(width, height, title, nullptr, nullptr);
		glfwMakeContextCurrent(m_window);
		glfwSetWindowUserPointer(m_window, &m_data);

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{ 
			std::cout << "Could not initialize GLAD" << std::endl;
			exit(EXIT_FAILURE);
		}

		glfwSetWindowCloseCallback(
			m_window, 
			[](GLFWwindow* window) {
				auto data = reinterpret_cast<CallbackData*>(glfwGetWindowUserPointer(window));
				WindowCloseEvent event;
				data->func(event);
			});
	}

	void Window::update()
	{
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glfwSwapBuffers(m_window);
		glfwPollEvents();
	}
}
