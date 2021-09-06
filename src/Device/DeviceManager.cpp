#include <AudioPlusPlus/Device/DeviceManager.h>
#include <AudioPlusPlus/Log/Log.h>

namespace AudioPlusPlus
{
	DeviceManager* DeviceManager::instance = nullptr;

	DeviceManager& DeviceManager::Get()
	{
		if (instance == nullptr)
			instance = new DeviceManager();

		return *instance;
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
			devices.emplace_back(i);
		}
	}

	const Device& DeviceManager::GetDefaultOutputDevice() const
	{
		return devices[Pa_GetDefaultOutputDevice()];
	}

	const Device& DeviceManager::GetDefaultInputDevice() const
	{
		return devices[Pa_GetDefaultInputDevice()];
	}

	const std::vector<Device>& DeviceManager::GetDevices() const
	{
		return devices;
	}

	int DeviceManager::GetSize() const
	{
		return devices.size();
	}

	const Device& DeviceManager::at(int index) const
	{
		return devices[index];
	}

	DeviceManager::~DeviceManager()
	{

	}
}