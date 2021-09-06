#pragma once
#include <AudioPlusPlus/Device/DeviceManager.h>
#include <AudioPlusPlus/File/WriteFile.h>
#include <AudioPlusPlus/Stream/Stream.h>

namespace AudioPlusPlus
{
	class Recorder
	{
		public:
			static Recorder& Get();

			static int Record(WriteFile& file, Stream& stream,
				const Device& device = DeviceManager::Get().GetDefaultInputDevice());

			static int Close(Stream& stream);

		private:
			static Recorder* instance;

			Recorder();
			~Recorder();
	};
}