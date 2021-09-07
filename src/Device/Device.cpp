#include <AudioPlusPlus/Device/Device.h>

namespace AudioPlusPlus
{
	Device::Device(int index)
		: index(index)
	{
		input = (Pa_GetDeviceInfo(index)->maxInputChannels > 0);
		output = (Pa_GetDeviceInfo(index)->maxOutputChannels > 0);
	}

	bool Device::operator==(const Device& rhs) const
	{
		return index == rhs.GetIndex();
	}

	const PaDeviceInfo* Device::GetInfo() const
	{
		return Pa_GetDeviceInfo(index);
	}

	int Device::GetIndex() const
	{
		return index;
	}

	bool Device::IsActive() const
	{
		//TODO(Callum): Check stream manager for if this device is in use
		return true;
	}

	bool Device::IsInput() const
	{
		return input;
	}

	bool Device::IsOutput() const
	{
		return output;
	}

	Device::~Device()
	{

	}
}