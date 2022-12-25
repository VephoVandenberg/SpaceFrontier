#pragma once

#include <functional>
#include <glfw3.h>

#include "event.h"

namespace GAME_NAMESPACE
{
	struct CallbackData
	{
		using EventCallbackFn = std::function<void(Event&)>;
		EventCallbackFn func;
	};

	class Window
	{
	public:
		Window(CallbackData& data);
		~Window(); 

		void update();

		Window(const Window&) = delete;
		Window(const Window&&) = delete;
		Window& operator=(const Window&) = delete;
		Window& operator=(const Window&&) = delete;

	private:
		void init();

		CallbackData m_data;

		GLFWwindow* m_window = nullptr;
	};
}
