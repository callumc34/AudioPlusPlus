#include <AudioPlusPlus/Device/DeviceManager.h>
#include <AudioPlusPlus/Log/Log.h>

namespace AudioPlusPlus
{
	DeviceManager& DeviceManager::Get()
	{
		static DeviceManager instance;

		return instance;
	}
	
	DeviceManager::DeviceManager()
	{
		int count = Pa_GetDeviceCount();
		if (count < 0)
		{
			AUDIO_CORE_ERROR("No devices found - error: " + std::string(Pa_GetErrorText(count)));
			return;
		}
		devices.reserve(Pa_GetDeviceCount());
		for (int i = 0; i < Pa_GetDeviceCount(); i++)
		{
			devices.push_back(new Device(i));
		}
	}

	const Device& DeviceManager::GetDefaultOutputDevice() const
	{
		return *devices[Pa_GetDefaultOutputDevice()];
	}

	const Device& DeviceManager::GetDefaultInputDevice() const
	{
		return *devices[Pa_GetDefaultInputDevice()];
	}

	const std::vector<Device*>& DeviceManager::GetDevices() const
	{
		return devices;
	}

	int DeviceManager::GetSize() const
	{
		return (int)devices.size();
	}

	const Device& DeviceManager::at(int index) const
	{
		return *devices[index];
	}

	DeviceManager::~DeviceManager()
	{
		for (auto device : devices)
		{
			delete device;
		}
	}
}