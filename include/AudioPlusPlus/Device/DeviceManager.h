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
			 * @brief      Gets the default output Device.
			 *
			 * @return     The default output Device.
			 */
			const Device& GetDefaultOutputDevice() const;

			/**
			 * @brief      Gets the default input Device.
			 *
			 * @return     The default input Device.
			 */
			const Device& GetDefaultInputDevice() const;

			/**
			 * @brief      Gets a list of all the Devices.
			 *
			 * @return     The Devices.
			 */
			const std::vector<Device*>& GetDevices() const;

			/**
			 * @brief      Gets the size of the array containing the Devices.
			 *
			 * @return     The size of the array containing the Devices.
			 */
			int GetSize() const;

			/**
			 * @brief      Returns the Device at a given index.
			 *
			 * @param[in]  index  The index
			 *
			 * @return     The Device.
			 */
			const Device& at(int index) const;

		private:
			DeviceManager();
			~DeviceManager();

			/* List of AudioPlusPlus Devices */
			std::vector<Device*> devices;

			friend class Stream;
	};
}