#pragma once
#include <AudioPlusPlus/File/File.h>
#include <portaudio.h>

namespace AudioPlusPlus
{
	/**
	 * @brief      Class to read audio data from a file supported by libsndfile
	 */
	class IReadFile : public IFile
	{
		public:
			/**
			 * @brief      Creates a new file instance for a file that can be read from.
			 *
			 * @param[in]  path  The file path
			 */
			IReadFile(const std::string& path);
			~IReadFile();

		protected:
			/**
			 * @brief      Reads from the file to the portaudio buffer.
			 *
			 * @param[in]  inputBuffer      The input buffer
			 * @param      outputBuffer     The output buffer
			 * @param[in]  framesPerBuffer  The frames per buffer
			 * @param[in]  timeInfo         The time information
			 * @param[in]  statusFlags      The status flags
			 * @param      userData         The user data
			 *
			 * @return     1 if file is fully read else 0.
			 */
			virtual int ReadToBuffer(
				const void* inputBuffer, void* outputBuffer,
				unsigned long framesPerBuffer,
				const PaStreamCallbackTimeInfo* timeInfo,
				PaStreamCallbackFlags statusFlags,
				void* userData
			) = 0;

			friend class Stream;
	};
}