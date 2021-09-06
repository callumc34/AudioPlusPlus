#pragma once
#include <AudioPlusPlus/File/File.h>
#include <portaudio.h>

namespace AudioPlusPlus
{
	class ReadFile : public IFile
	{
		public:
			ReadFile(const std::string& path);
			~ReadFile();

			int Close() override;

		private:
			int ReadToBuffer(
				const void* inputBuffer, void* outputBuffer,
				unsigned long framesPerBuffer,
				const PaStreamCallbackTimeInfo* timeInfo,
				PaStreamCallbackFlags statusFlags,
				void* userData
			);

			friend class Stream;
	};
}