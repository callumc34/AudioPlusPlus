#pragma once
#include <AudioPlusPlus/Device/DeviceManager.h>
#include <AudioPlusPlus/File/WriteFile.h>
#include <AudioPlusPlus/Stream/StreamManager.h>

namespace AudioPlusPlus
{
	/**
	 * @brief      Static class for easier recording interaction with the library.
	 */
	class Recorder
	{
		public:
			/**
			 * @brief      Load a IWriteFile into the input Stream.
			 *
			 * @param      file    The file
			 * @param      stream  The Stream
			 * @param[in]  device  The Device
			 *
			 * @return     Error code.
			 */
			static int Load(IWriteFile& file, Stream& stream,
				const Device& device = DeviceManager::Get().GetDefaultInputDevice());

			/**
			 * @brief      Load a IWriteFile into a Stream and return the corresponding Stream.
			 *
			 * @param      file    The file
			 * @param[in]  device  The Device
			 *
			 * @return     The Stream the IWriteFile is loaded into.
			 */
			static Stream* Load(IWriteFile& file, const Device& device = DeviceManager::Get().GetDefaultInputDevice());

			/**
			 * @brief      Closes recording of a Stream.
			 *
			 * @param      stream  The Stream
			 *
			 * @return     Error code.
			 */
			static int Close(Stream* stream);
	};
}