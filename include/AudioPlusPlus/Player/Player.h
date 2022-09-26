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
			 * @brief      Load a IReadFile into a Stream.
			 *
			 * @param      file    The file
			 * @param      stream  The Stream
			 * @param[in]  device  The Device
			 *
			 * @return     Error code.
			 */
			static int Load(IReadFile& file, Stream& stream,
				const Device& device = DeviceManager::Get().GetDefaultOutputDevice());

			/**
			 * @brief      Load a IReadFile and return the corresponding Stream.
			 *
			 * @param      file    The file
			 * @param[in]  device  The Device
			 *
			 * @return     The Stream the file is loaded into.
			 */
			static Stream* Load(IReadFile& file, const Device& device = DeviceManager::Get().GetDefaultOutputDevice());

			/**
			 * @brief      Close playback of a Stream.
			 *
			 * @param      stream  The Stream
			 *                     
			 * @return     Error code.
			 */
			static int Close(Stream* stream);
	};
}