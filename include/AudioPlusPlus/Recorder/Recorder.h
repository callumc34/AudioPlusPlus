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
			 * @brief      Load a WriteFile into the input stream.
			 *
			 * @param      file    The file
			 * @param      stream  The stream
			 * @param[in]  device  The device
			 *
			 * @return     Error code.
			 */
			static int Load(WriteFile& file, Stream& stream,
				const Device& device = DeviceManager::Get().GetDefaultInputDevice());

			/**
			 * @brief      Load a WriteFile into a stream and return the corresponding stream.
			 *
			 * @param      file    The file
			 * @param[in]  device  The device
			 *
			 * @return     The stream the WriteFile is loaded into.
			 */
			static Stream* Load(WriteFile& file, const Device& device = DeviceManager::Get().GetDefaultInputDevice());

			/**
			 * @brief      Closes recording of a stream.
			 *
			 * @param      stream  The stream
			 *
			 * @return     Error code.
			 */
			static int Close(Stream* stream);
	};
}