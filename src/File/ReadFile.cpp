#include <AudioPlusPlus/File/ReadFile.h>
#ifdef __linux__
#include <cstring>
#endif

namespace AudioPlusPlus
{
	ReadFile::ReadFile(const std::string& path)
		: IFile(path, SFM_READ, 0, 0)
	{
		data->length = static_cast<double>(this->frames() / this->samplerate());
		data->sampleRate = this->samplerate();
		data->channels = this->channels();
	}

	int ReadFile::Close()
	{
		return 0;
	}

	int ReadFile::ReadToBuffer(
		const void* inputBuffer, void* outputBuffer,
		unsigned long framesPerBuffer,
		const PaStreamCallbackTimeInfo* timeInfo,
		PaStreamCallbackFlags statusFlags,
		void* userData
	)
	{
		//unused suppression
		(void)inputBuffer;
		(void)userData;
		(void)statusFlags;

		float* out = (float*)outputBuffer;
		int finished = paContinue;

		sf_count_t numRead;

		//Clear output buffer
		memset(out, 0, sizeof(float) * framesPerBuffer * data->channels);

		numRead = read(out, framesPerBuffer * data->channels);

		if (numRead < framesPerBuffer)
			finished = paComplete;

		return finished;
	}

	ReadFile::~ReadFile()
	{

	}
}