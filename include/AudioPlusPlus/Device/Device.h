#pragma once
#include <portaudio.h>
#include <vector>

namespace AudioPlusPlus
{

	class Device
	{
		public:
			bool operator==(const Device& rhs) const;

			const PaDeviceInfo* GetInfo() const;
			int GetIndex() const;
			bool IsActive() const;
			//Assuming one device can have both input and output channels
			bool IsInput() const;
			bool IsOutput() const;

		private:
			Device(int index);
			~Device();

			int index;
			bool input;
			bool output;

			friend class DeviceManager;
	};
}