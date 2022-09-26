#include <AudioPlusPlus/File/SndReadFile.h>
#include <AudioPlusPlus/Stream/Stream.h>
#include <AudioPlusPlus/Log/Log.h>

namespace AudioPlusPlus
{
    SndReadFile::SndReadFile(const std::string& path)
        : IReadFile(path), SndfileHandle(path, SFM_READ)
    {
        data.length = static_cast<double>(frames() / samplerate());
        data.sampleRate = samplerate();
        data.channels = channels();
    }

	double SndReadFile::GetPosition()
	{
		return (double)seek(0, SEEK_CUR) / samplerate();
	}

	int SndReadFile::Close()
	{
		closed = true;
		return 0;
	}

	int SndReadFile::ReadToBuffer(
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

		if (closed)
		{
			return paComplete;
		}

		Stream::StreamConfig* cfg = static_cast<Stream::StreamConfig*>(userData);

		float* out = (float*)outputBuffer;
		int finished = paContinue;

		// Clear output buffer
		memset(out, 0, sizeof(float) * framesPerBuffer * data.channels);

		if (cfg->seek)
		{
			seek(static_cast<sf_count_t>(cfg->position), SEEK_SET);
			cfg->seek = false;
		}

		sf_count_t numRead = read(out, static_cast<sf_count_t>(framesPerBuffer) * data.channels);

		if (cfg->loop)
		{
			sf_count_t position = seek(0, SEEK_CUR);
			if (position < cfg->start * samplerate() || position >= cfg->end * samplerate())
			{
				seek((sf_count_t)(cfg->start * samplerate()), SEEK_SET);
			}
		}

		if (cfg->volume != 1)
		{
			for (unsigned long i = 0; i < framesPerBuffer * data.channels; i++)
			{
				*out *= static_cast<float>(cfg->volume);
				out++;
			}
		}

		if (numRead < framesPerBuffer)
			finished = paComplete;

		return finished;
	}

	SndReadFile::~SndReadFile()
	{

	}
}