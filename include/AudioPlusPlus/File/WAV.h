#pragma once
#include <AudioPlusPlus/File/File.h>

namespace AudioPlusPlus
{
	class WAV : public File
	{
		public:
			~WAV();

			int FillBuffer(
				const void* inputBuffer, void* outputBuffer,
				unsigned long framesPerBuffer,
				const PaStreamCallbackTimeInfo* timeInfo,
				PaStreamCallbackFlags statusFlags,
				void* userData
			) override;

		private:
			WAV(const std::string& path);
			friend class File;
	};
}