#pragma once
#include <AudioPlusPlus/Device/DeviceManager.h>
#include <AudioPlusPlus/File/WriteFile.h>
#include <AudioPlusPlus/Stream/StreamManager.h>

namespace AudioPlusPlus
{
	class Recorder
	{
		public:
			static int Load(WriteFile& file, Stream& stream,
				const Device& device = DeviceManager::Get().GetDefaultInputDevice());

			static Stream* Load(WriteFile& file, const Device& device = DeviceManager::Get().GetDefaultInputDevice());

			static int Close(Stream* stream);
	};
}