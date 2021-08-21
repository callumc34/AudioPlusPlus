#pragma once
#include <AudioPlusPlus/Device/Device.h>
#include <AudioPlusPlus/Player/Stream.h>

namespace AudioPlusPlus
{
	class Player
	{
		public:
			static Player& Get();

			int Open(Stream* stream, PaStreamParameters OutputParamaters);

		private:
			static Player* instance;

			Player();
			~Player();
	
			Stream* stream = nullptr;
			PaStream* DataStream = 0;
	};
}