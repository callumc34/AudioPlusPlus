#include <AudioPlusPlus/File/AIFF.h>

namespace AudioPlusPlus
{
	AIFF::AIFF(const std::string& path)
	{
		data.path = path;
		data.format = FileFormat::AIFF;
	}

	int AIFF::FillBuffer(
		const void* inputBuffer, void* outputBuffer,
		unsigned long framesPerBuffer,
		const PaStreamCallbackTimeInfo* timeInfo,
		PaStreamCallbackFlags statusFlags,
		void* userData
	)
	{
		return paContinue;
	}

	AIFF::~AIFF()
	{

	}
}