#include <iostream>

#include "../include/window.h"

using namespace GAME_NAMESPACE::System;

constexpr float width = 1600.0f;
constexpr float height = 1000.0f;
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

	glfwSetFramebufferSizeCallback(
		m_window,
		[](GLFWwindow* window, int width, int height) {
			glViewport(0, 0, width, height);
		});
}

void Window::clearScreen()
{
	glClearColor(0.0f, 0.0f, 0.04f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}

void Window::update()
{
	glfwSwapBuffers(m_window);
	glfwPollEvents();
}

