#pragma once


namespace GAME_NAMESPACE
{
	namespace System
	{
		enum class EventType
		{
			CLOSE = 0,
			KEY_PRESS,
			KEY_RELEASE,
			KEY_REPEAT
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
	}

}