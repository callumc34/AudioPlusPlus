#pragma once
#include <AudioPlusPlus/File/File.h>
#include <portaudio.h>

namespace AudioPlusPlus
{
	class WriteFile : public IFile
	{
		public:
			WriteFile(const std::string& path, int format = SF_FORMAT_WAV | SF_FORMAT_PCM_16, int channels = 2, int samplerate = 44100);
			~WriteFile();

			int Close() override;

		private:
			int WriteToBuffer(
				const void* inputBuffer, void* outputBuffer,
				unsigned long framesPerBuffer,
				const PaStreamCallbackTimeInfo* timeInfo,
				PaStreamCallbackFlags statusFlags,
				void* userData
			);

		friend class Stream;
	};
}