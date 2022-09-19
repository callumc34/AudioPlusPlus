#pragma once
#include <AudioPlusPlus/Device/DeviceManager.h>
#include <AudioPlusPlus/File/ReadFile.h>
#include <AudioPlusPlus/Stream/StreamManager.h>

namespace AudioPlusPlus
{
	/**
	 * @brief      Static class for easier playback interaction with the library.
	 */
	class Player
	{
		public:
			/**
			 * @brief      Load a ReadFile into a stream.
			 *
			 * @param      file    The file
			 * @param      stream  The stream
			 * @param[in]  device  The device
			 *
			 * @return     Error code.
			 */
			static int Load(ReadFile& file, Stream& stream,
				const Device& device = DeviceManager::Get().GetDefaultOutputDevice());

			/**
			 * @brief      Load a ReadFile and return the corresponding stream.
			 *
			 * @param      file    The file
			 * @param[in]  device  The device
			 *
			 * @return     The stream the file is loaded into.
			 */
			static Stream* Load(ReadFile& file, const Device& device = DeviceManager::Get().GetDefaultOutputDevice());

			/**
			 * @brief      Close playback of a stream.
			 *
			 * @param      stream  The stream
			 *                     
			 * @return     Error code.
			 */
			static int Close(Stream* stream);
	};
}