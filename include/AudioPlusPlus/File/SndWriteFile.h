#pragma once
#include <AudioPlusPlus/File/WriteFile.h>
#include <sndfile.hh>

namespace AudioPlusPlus
{
	/**
	 * @brief      Class to write data to a file using libsndfile.
	 */
	class SndWriteFile : public IWriteFile, private SndfileHandle
	{
		public:
			/**
			 * @brief      Constructs a new SndWriteFile for writing data to a file using SndfileHandle's IO operations.
			 *
			 * @param[in]  path        The path
			 * @param[in]  format      The format
			 * @param[in]  channels    The channels
			 * @param[in]  samplerate  The samplerate
			 */
			SndWriteFile(const std::string& path, int format = SF_FORMAT_WAV | SF_FORMAT_PCM_16,
				int channels = 2, int samplerate = 44100);
			~SndWriteFile();

			double GetPosition();
			int Close();

		private:
			/** Whether the file is closed or not*/
			bool closed = false;

			int WriteToBuffer(
				const void* inputBuffer, void* outputBuffer,
				unsigned long framesPerBuffer,
				const PaStreamCallbackTimeInfo* timeInfo,
				PaStreamCallbackFlags statusFlags,
				void* userData
			);
	};
}

