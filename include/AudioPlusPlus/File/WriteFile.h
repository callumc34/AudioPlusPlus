#pragma once
#include <AudioPlusPlus/File/File.h>
#include <portaudio.h>

namespace AudioPlusPlus
{
	/**
	 * @brief      Class to write audio encoded data to a file format supported by libsndfile.
	 */
	class IWriteFile : public IFile
	{
		public:
			/**
			 * @brief      Constructs a new file to write from the input buffer into.
			 *
			 * @param[in]  path        The path
			 * @param[in]  format      The format
			 * @param[in]  channels    The channels
			 * @param[in]  samplerate  The samplerate
			 */
			IWriteFile(const std::string& path);

			/**
			 * @brief      Destructor for a IWriteFile object.
			 */
			~IWriteFile();

		protected:
			/**
			 * @brief      Write from the port audio input buffer to a file.
			 *
			 * @param[in]  inputBuffer      The input buffer
			 * @param      outputBuffer     The output buffer
			 * @param[in]  framesPerBuffer  The frames per buffer
			 * @param[in]  timeInfo         The time information
			 * @param[in]  statusFlags      The status flags
			 * @param      userData         The user data
			 *
			 * @return     1 if finished else 0.
			 */
			virtual int WriteToBuffer(
				const void* inputBuffer, void* outputBuffer,
				unsigned long framesPerBuffer,
				const PaStreamCallbackTimeInfo* timeInfo,
				PaStreamCallbackFlags statusFlags,
				void* userData
			) = 0;

			friend class Stream;
	};
}