#pragma once

#include "../game_object.h"


namespace GAME_NAMESPACE
{
	namespace GameModule
	{
		class SpaceObj : public GameObj
		{
		public:
			SpaceObj() = default;
			virtual ~SpaceObj() = default;
			SpaceObj(SpaceObj&&) = default;
			SpaceObj& operator=(SpaceObj&&) = default;

			SpaceObj(const SpaceObj&) = delete;
			SpaceObj& operator=(const SpaceObj&) = delete;
		};
	}
}