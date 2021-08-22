#pragma once
#include <AudioPlusPlus/File/File.h>

namespace AudioPlusPlus
{
	class AIFF : public File
	{
		public:
			~AIFF();

			int FillBuffer(
				const void* inputBuffer, void* outputBuffer,
				unsigned long framesPerBuffer,
				const PaStreamCallbackTimeInfo* timeInfo,
				PaStreamCallbackFlags statusFlags,
				void* userData
			) override;

		private:
			AIFF(const std::string& path);
			friend class File;
	};
}