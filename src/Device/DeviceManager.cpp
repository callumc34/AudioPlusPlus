#include <AudioPlusPlus/Device/DeviceManager.h>
#include <AudioPlusPlus/AudioPlusPlus.h>

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
		count = Pa_GetDeviceCount();
		if (count < 0)
		{
			AUDIO_CORE_ERROR("Device count returned error: " + std::string(Pa_GetErrorText(count)));
			Exit();
			return;
		}

		devices.reserve(count);
		for (int i = 0; i < count; i++)
		{
			devices.emplace_back(i);
		}
	}

	const std::vector<Device>& DeviceManager::GetDevices()
	{
		return devices;
	}

	PaDeviceIndex DeviceManager::GetActiveDevice()
	{
		for (int i = 0; i < devices.size(); i++)
		{
			if (devices[i].active)
			{
				return i;
			}
		}
		return -1;
	}

	int DeviceManager::GetCount()
	{
		return count;
	}

	int DeviceManager::SetActiveDevice(int index)
	{
		//TODO(Callum): Restart stream with device active
		//Add actual functionality to these changed states
		for (int i = 0; i < devices.size(); i++)
		{
			if (devices[i].active)
			{
				devices[i].active = false;
			}
		}
		devices[index].active = true;

		return 0;
	}

	DeviceManager::~DeviceManager()
	{

	}
}