#pragma once
#include <AudioPlusPlus/Device/Device.h>
#include <vector>

namespace AudioPlusPlus
{
	class DeviceManager
	{
		public:
			static DeviceManager& Get();

			const Device& GetDefaultOutputDevice() const;
			const Device& GetDefaultInputDevice() const;

			const std::vector<Device>& GetDevices() const;
			int GetSize() const;

			const Device& at(int index) const;

		private:
			static DeviceManager* instance;

			DeviceManager();
			~DeviceManager();

			std::vector<Device> devices;

			friend class Stream;
	};
}