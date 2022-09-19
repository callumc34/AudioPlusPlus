#pragma once
#include <portaudio.h>
#include <vector>

namespace AudioPlusPlus
{
	/**
	 * @brief      Class containing information for an audio device.
	 */
	class Device
	{
		public:
			/**
			 * @brief      Checks the two devices are the same.
			 *
			 * @param[in]  rhs   The right hand side.
			 *
			 * @return     The result of the equality.
			 */
			bool operator==(const Device& rhs) const;

			/**
			 * @brief      Gets the PaDeviceInfo of the device.
			 *
			 * @return     The information.
			 */
			const PaDeviceInfo* GetInfo() const;

			/**
			 * @brief      Gets the index of the device in PortAudio.
			 *
			 * @return     The index.
			 */
			int GetIndex() const;

			/**
			 * @brief      Determines if the device is in use.
			 *
			 * @return     True if active, False otherwise.
			 */
			bool IsActive() const;

			// Assuming one device can have both input and output channels

			/**
			 * @brief      Determines if the device is capable of input.
			 *
			 * @return     True if device can input, False otherwise.
			 */
			bool IsInput() const;

			/**
			 * @brief      Determines if the device is capable of output.
			 *
			 * @return     True if output, False otherwise.
			 */
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