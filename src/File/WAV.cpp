#include <AudioPlusPlus/File/WAV.h>

namespace AudioPlusPlus
{
	WAV::WAV(const std::string& path)
	{
		data.path = path;
		data.format = FileFormat::Wave;
	}

	int WAV::FillBuffer(
			const void* inputBuffer, void* outputBuffer,
			unsigned long framesPerBuffer,
			const PaStreamCallbackTimeInfo* timeInfo,
			PaStreamCallbackFlags statusFlags,
			void* userData
		)
	{
		return paContinue;
	}

	WAV::~WAV()
	{

	}
}