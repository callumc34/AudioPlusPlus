#pragma once
#include <AudioPlusPlus/Device/Device.h>
#include <vector>

namespace AudioPlusPlus
{
	/**
	 * @brief      Singleton instance class to access the list of devices.
	 */
	class DeviceManager
	{
		public:
			DeviceManager(DeviceManager const&) = delete;
			void operator=(DeviceManager const&) = delete;

			/**
			 * @brief      Gets the DeviceManager instance.
			 *
			 * @return     Singleton instance of the DeviceManager.
			 */
			static DeviceManager& Get();

			/**
			 * @brief      Gets the default output device.
			 *
			 * @return     The default output device.
			 */
			const Device& GetDefaultOutputDevice() const;

			/**
			 * @brief      Gets the default input device.
			 *
			 * @return     The default input device.
			 */
			const Device& GetDefaultInputDevice() const;

			/**
			 * @brief      Gets a list of all the devices.
			 *
			 * @return     The devices.
			 */
			const std::vector<Device*>& GetDevices() const;

			/**
			 * @brief      Gets the size of the array containing the devices.
			 *
			 * @return     The size of the array containing the devices.
			 */
			int GetSize() const;

			/**
			 * @brief      Returns the device at a given index.
			 *
			 * @param[in]  index  The index
			 *
			 * @return     The device.
			 */
			const Device& at(int index) const;

		private:
			DeviceManager();
			~DeviceManager();

			/* List of AudioPlusPlus devices */
			std::vector<Device*> devices;

			friend class Stream;
	};
}