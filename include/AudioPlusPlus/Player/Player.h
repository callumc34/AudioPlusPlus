#pragma once
#include <AudioPlusPlus/Device/DeviceManager.h>
#include <AudioPlusPlus/File/ReadFile.h>
#include <AudioPlusPlus/Stream/StreamManager.h>

namespace AudioPlusPlus
{
	class Player
	{
		public:
			static Player& Get();

			static int Play(ReadFile& file, Stream& stream,
				const Device& device = DeviceManager::Get().GetDefaultOutputDevice());

			static Stream* Play(ReadFile& file, const Device& device = DeviceManager::Get().GetDefaultOutputDevice());

			static int Close(Stream& stream);

		private:
			static Player* instance;

			Player();
			~Player();
	};
}