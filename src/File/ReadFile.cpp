#include <AudioPlusPlus/File/ReadFile.h>
#include <AudioPlusPlus/Stream/Stream.h>
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
		// Unused suppression
		(void)inputBuffer;
		(void)statusFlags;

		Stream::StreamConfig* cfg = static_cast<Stream::StreamConfig*>(userData);

		float* out = (float*)outputBuffer;
		int finished = paContinue;

		// Clear output buffer
		memset(out, 0, sizeof(float) * framesPerBuffer * data->channels);

		if (cfg->seek)
		{
			seek(static_cast<sf_count_t>(cfg->position), SEEK_SET);
			cfg->seek = false;
		}

		sf_count_t numRead = read(out, static_cast<sf_count_t>(framesPerBuffer) * data->channels);

		if (cfg->loop)
		{
			sf_count_t position = seek(0, SEEK_CUR);
			if (position < cfg->start * samplerate() || position >= cfg->end * samplerate())
			{
				seek(cfg->start * samplerate(), SEEK_SET);
			}
		}

		if (cfg->volume != 1)
		{
			for (unsigned long i = 0; i < framesPerBuffer * data->channels; i++)
			{
				*out *= static_cast<float>(cfg->volume);
				out++;
			}
		}

		if (numRead < framesPerBuffer)
			finished = paComplete;

		return finished;
	}

	ReadFile::~ReadFile()
	{

	}
}