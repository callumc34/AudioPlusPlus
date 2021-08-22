#pragma once
#include <AudioPlusPlus/File/File.h>
#include <AudioPlusPlus/Device/Device.h>

namespace AudioPlusPlus
{
	class Player
	{
		public:
			static Player& Get();

			int Play(File* file, Stream* stream, Device* device = nullptr);

		private:
			static Player* instance;

			Player();
			~Player();
	};
}