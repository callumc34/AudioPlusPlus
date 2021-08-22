#include <AudioPlusPlus/File/MP3.h>

namespace AudioPlusPlus
{
	MP3::MP3(const std::string& path)
	{
		data.path = path;
		data.format = FileFormat::MP3;
	}

	int MP3::FillBuffer(
		const void* inputBuffer, void* outputBuffer,
		unsigned long framesPerBuffer,
		const PaStreamCallbackTimeInfo* timeInfo,
		PaStreamCallbackFlags statusFlags,
		void* userData
	)
	{
		return paContinue;
	}

	MP3::~MP3()
	{

	}
}