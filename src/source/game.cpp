#include "../include/game.h"

namespace GAME_NAMESPACE
{
	constexpr float width = 700.0f;
	constexpr float height = 800.0f;
	constexpr auto title = "SpaceFrontier";

	Game::InterfaceGLFWwindow::InterfaceGLFWwindow()
	{
		window = glfwCreateWindow(width, height, title, nullptr, nullptr);
	}

	Game::InterfaceGLFWwindow::~InterfaceGLFWwindow()
	{
		glfwDestroyWindow(window);
	}

	Game::Game()
	{
		init();
	}

	void Game::init()
	{
		if (!glfwInit())
		{
			std::cout << "Could not initialize GLFW" << std::endl;
			exit(EXIT_FAILURE);
		}
		 
		m_winInterface = std::make_unique<InterfaceGLFWwindow>();
	}

	void Game::run()
	{
		while (!glfwWindowShouldClose(m_winInterface->window))
		{
			glfwPollEvents();
		}
	}
}
