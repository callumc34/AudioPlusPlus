#pragma once
#include <AudioPlusPlus/Device/DeviceManager.h>
#include <AudioPlusPlus/File/ReadFile.h>
#include <AudioPlusPlus/Stream/Stream.h>

namespace AudioPlusPlus
{
	class Player
	{
		public:
			static Player& Get();

			static int Play(ReadFile& file, Stream& stream,
				const Device& device = DeviceManager::Get().GetDefaultOutputDevice());

			static int Close(Stream& stream);

		private:
			static Player* instance;

			Player();
			~Player();
	};
}