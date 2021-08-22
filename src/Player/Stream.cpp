#include <AudioPlusPlus/Player/Stream.h>

namespace AudioPlusPlus
{
	Stream::Stream()
	{

	}

	PaStream** Stream::Get()
	{
		return &stream;
	}

	PaError Stream::Start()
	{
		if (stream == 0)
			return paNotInitialized;

		PaError err = Pa_StartStream(stream);

		return err;
	}

	PaError Stream::Stop()
	{
		if (stream == 0)
			return paNotInitialized;

		PaError err = Pa_StopStream(stream);

		return err;
	}

	PaError Stream::Close()
	{
		if (stream == 0)
			return paNotInitialized;

		PaError err = Pa_CloseStream(stream);
		stream = 0;

		return err;
	}

	Stream::~Stream()
	{

	}
}