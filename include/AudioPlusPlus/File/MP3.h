#pragma once
#include <AudioPlusPlus/File/File.h>

namespace AudioPlusPlus
{
	class MP3 : public File
	{
		public:
			~MP3();

			int FillBuffer(
				const void* inputBuffer, void* outputBuffer,
				unsigned long framesPerBuffer,
				const PaStreamCallbackTimeInfo* timeInfo,
				PaStreamCallbackFlags statusFlags,
				void* userData
			) override;

		private:
			MP3(const std::string& path);
			friend class File;
	};
}