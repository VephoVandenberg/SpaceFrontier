#pragma once


namespace GAME_NAMESPACE
{
	enum class EventType
	{
		CLOSE = 0,
	};

	struct Event
	{
		inline virtual EventType getType() const = 0;
	};

	struct WindowCloseEvent : public Event
	{
		inline EventType getType() const override{ return EventType::CLOSE; }
	};

}