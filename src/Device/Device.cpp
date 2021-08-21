#include <AudioPlusPlus/Device/Device.h>

namespace AudioPlusPlus
{
	Device::Device(int index)
		: index(index)
	{

	}

	const PaDeviceInfo* Device::GetInfo()
	{
		return Pa_GetDeviceInfo(index);
	}

	int Device::GetIndex()
	{
		return index;
	}

	bool Device::IsActive()
	{
		return active;
	}

	Device::~Device()
	{

	}
}