#pragma once
#include <portaudio.h>

namespace AudioPlusPlus
{

	class Device
	{
		public:
			Device(int index);
			~Device();

			const PaDeviceInfo* GetInfo() const;
			int GetIndex() const;
			bool IsActive() const;
			//Assuming one device can have both input and output channels
			bool IsInput() const;
			bool IsOutput() const;

		private:
			int index;
			bool input;
			bool output;
	};
}