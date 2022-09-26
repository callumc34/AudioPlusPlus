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
			 * @brief      Checks that two Device's are the same.
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
			 * @brief      Gets the index of the Device in PortAudio.
			 *
			 * @return     The index.
			 */
			int GetIndex() const;

			/**
			 * @brief      Determines if the Device is in use.
			 *
			 * @return     True if active, False otherwise.
			 */
			bool IsActive() const;

			/**
			 * @brief      Determines if the Device is capable of input.
			 *
			 * @return     True if Device can input, False otherwise.
			 */
			bool IsInput() const;

			/**
			 * @brief      Determines if the Device is capable of output.
			 *
			 * @return     True if Device can output, False otherwise.
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