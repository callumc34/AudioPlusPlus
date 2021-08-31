#include <AudioPlusPlus/File/File.h>
#ifdef __linux__
#include <cstring>
#endif

namespace AudioPlusPlus
{
	File::File(const std::string& path)
		: SndfileHandle(path), tag(path)
	{
		data.path = path;
		data.sampleRate = samplerate();
		data.channels = channels();
	}

	int File::OpenStream(Stream* stream, PaStreamParameters OutputParameters)
	{
		//TODO(Callum): Fix config parameters
		//Also just fix in general
		PaError err = Pa_OpenStream(
			stream->Get(),
			nullptr,
			&OutputParameters,
			44100,
			paFramesPerBufferUnspecified,
			paClipOff,
			&File::AudioCallback,
			this
		);

		return 0;
	}

	const FileData& File::GetFileData()
	{
		return data;
	}

	int File::FillBuffer(
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
		memset(out, 0, sizeof(float) * framesPerBuffer * data.channels);

		numRead = read(out, framesPerBuffer * data.channels);

		if (numRead < framesPerBuffer)
			finished = paComplete;

		return finished;

	}

	int File::AudioCallback(
		const void* inputBuffer, void* outputBuffer,
		unsigned long framesPerBuffer,
		const PaStreamCallbackTimeInfo* timeInfo,
		PaStreamCallbackFlags statusFlags,
		void* userData
	)
	{
		return (static_cast<File*>(userData)->FillBuffer(
			inputBuffer, outputBuffer,
			framesPerBuffer,
			timeInfo,
			statusFlags,
			userData
		));
	}

	File::~File()
	{

	}
}