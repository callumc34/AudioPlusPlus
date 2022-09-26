#include <AudioPlusPlus/File/SndWriteFile.h>
#include <AudioPlusPlus/Stream/Stream.h>
#include <AudioPlusPlus/Log/Log.h>

namespace AudioPlusPlus
{
	SndWriteFile::SndWriteFile(const std::string& path, int format, int channels, int samplerate)
		: IWriteFile(path), SndfileHandle(path, SFM_RDWR, format, channels, samplerate)
	{
		data.sampleRate = samplerate;
		data.channels = channels;
	}

	double SndWriteFile::GetPosition()
	{
		return (double)seek(0, SEEK_CUR) / samplerate();
	}

	int SndWriteFile::Close()
	{
		closed = true;
		return 0;
	}

	int SndWriteFile::WriteToBuffer(
		const void* inputBuffer, void* outputBuffer,
		unsigned long framesPerBuffer,
		const PaStreamCallbackTimeInfo* timeInfo,
		PaStreamCallbackFlags statusFlags,
		void* userData
	)
	{
		//Unused variable warnings suppression
		(void)outputBuffer;
		(void)timeInfo;
		(void)statusFlags;
		(void)userData;

		//Convert to float 32
		const float* samples = (const float*)inputBuffer;

		int finished = paContinue;

		if (closed)
		{
			finished = paComplete;
		}

		sf_count_t writeCount = write(samples, static_cast<sf_count_t>(framesPerBuffer) * data.channels);

		if (writeCount <= 0)
		{
			AUDIO_ERROR("Error writing to file...");
			return paComplete;
		}

		return finished;
	}

	SndWriteFile::~SndWriteFile()
	{

	}
}