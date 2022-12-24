#pragma once

#include <iostream>
#include <memory>

#include <glfw3.h>

namespace GAME_NAMESPACE
{
	class Game
	{
	public:
		Game();
		~Game() = default;

		void run();

		Game(const Game&) = delete;
		Game(const Game&&) = delete;
		Game& operator=(const Game&) = delete;
		Game& operator=(const Game&&) = delete;

	private:
		void init();

		struct InterfaceGLFWwindow
		{
			GLFWwindow* window;

			InterfaceGLFWwindow();
			~InterfaceGLFWwindow();

			InterfaceGLFWwindow(const InterfaceGLFWwindow&) = delete;
			InterfaceGLFWwindow(const InterfaceGLFWwindow&&) = delete;
			InterfaceGLFWwindow& operator=(const InterfaceGLFWwindow&) = delete;
			InterfaceGLFWwindow& operator=(const InterfaceGLFWwindow&&) = delete;
			
		};

		std::unique_ptr<InterfaceGLFWwindow> m_winInterface;
	};
}