#pragma once
#include <AudioPlusPlus/Device/DeviceManager.h>
#include <AudioPlusPlus/File/ReadFile.h>
#include <AudioPlusPlus/Stream/StreamManager.h>

namespace AudioPlusPlus
{
	class Player
	{
		public:
			static int Load(ReadFile& file, Stream& stream,
				const Device& device = DeviceManager::Get().GetDefaultOutputDevice());

			static Stream* Load(ReadFile& file, const Device& device = DeviceManager::Get().GetDefaultOutputDevice());

			static void PlayFor();
			static void PlayFor(int ms);

			static int Close(Stream* stream);
	};
}