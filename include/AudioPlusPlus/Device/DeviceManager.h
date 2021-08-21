#pragma once
#include <AudioPlusPlus/Device/Device.h>
#include <vector>

namespace AudioPlusPlus
{
	class DeviceManager
	{
		public:
			static DeviceManager& Get();

			DeviceManager();
			~DeviceManager();

			const std::vector<Device>& GetDevices();
			PaDeviceIndex GetActiveDevice();
			int GetCount();

			int SetActiveDevice(int index);

		private:
			static DeviceManager* instance;

			int count;
			std::vector<Device> devices;
	};
}