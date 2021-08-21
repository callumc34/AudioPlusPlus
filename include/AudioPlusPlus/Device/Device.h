#pragma once
#include <portaudio.h>

namespace AudioPlusPlus
{
	//Forward declare for friend
	class DeviceManager;

	class Device
	{
		public:
			Device(int index);
			~Device();

			const PaDeviceInfo* GetInfo();
			int GetIndex();
			bool IsActive();

		private:
			int index;
			bool active = false;

			friend DeviceManager;
	};
}