#pragma once
#include <AudioPlusPlus/Device/Device.h>

namespace AudioPlusPlus
{
	class Player
	{
		public:
			static Player& Get();

		private:
			static Player* instance;

			Player();
			~Player();
	};
}