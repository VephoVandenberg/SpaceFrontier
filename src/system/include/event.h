#pragma once

#include <glm/glm.hpp>

namespace GAME_NAMESPACE
{
	namespace System
	{
		enum class EventType
		{
			CLOSE = 0,
			KEY_PRESS,
			KEY_RELEASE,
			KEY_REPEAT,
			MOUSE_MOVE
		};

		struct Event
		{
			inline virtual EventType getType() const = 0;
		};

		struct WindowCloseEvent : public Event
		{
			inline EventType getType() const override { return EventType::CLOSE; }
		};

		struct KeyPressEvent : public Event
		{
			int key;

			inline EventType getType() const override { return EventType::KEY_PRESS; }
		};

		struct KeyReleaseEvent : public Event
		{
			int key;

			inline EventType getType() const override { return EventType::KEY_RELEASE; }
		};

		struct KeyRepeatEvent : public Event
		{
			int key;

			inline EventType getType() const override { return EventType::KEY_REPEAT; }
		};

		struct MouseMoveEvent : public Event
		{
			glm::vec3 position;

			inline EventType getType() const override { return EventType::MOUSE_MOVE; }
		};
	}
}
