#include <AudioPlusPlus/Stream/Stream.h>

namespace AudioPlusPlus
{
	Stream::Stream()
	{

	}

	PaError Stream::SetDevice(int index)
	{
		this->device = &DeviceManager::Get().devices[index];
		return 0;
	}
	
	PaError Stream::SetDevice(const Device& device)
	{
		return SetDevice(device.GetIndex());
	}

	const Device* Stream::GetDevice()
	{
		return device;
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
		active = false;

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

	PaStream** Stream::GetBuffer()
	{
		return &stream;
	}

	PaError Stream::OpenPlaybackStream(ReadFile& file)
	{
		if (stream != 0)
		{
			return paStreamIsNotStopped;
		}

		PaStreamParameters OutputParameters{
			device->GetIndex(),
			file.GetFileData()->channels,
			paFloat32,
			device->GetInfo()->defaultLowOutputLatency,
			NULL
		};

		int err = Pa_OpenStream(
			&stream,
			nullptr,
			&OutputParameters,
			file.GetFileData()->sampleRate,
			paFramesPerBufferUnspecified,
			paClipOff,
			&Stream::OpenPlaybackStreamCallback,
			static_cast<void*>(&file)
		);

		if (!err)
		{
			active = true;
		}
		return err;
	}

	PaError Stream::OpenRecordingStream(WriteFile& file)
	{
		if (stream != 0)
		{
			return paStreamIsNotStopped;
		}

		PaStreamParameters InputParameters{
			device->GetIndex(),
			device->GetInfo()->maxInputChannels,
			paFloat32,
			device->GetInfo()->defaultLowInputLatency,
			NULL
		};

		int err = Pa_OpenStream(
			&stream,
			&InputParameters,
			nullptr,
			file.GetFileData()->sampleRate,
			paFramesPerBufferUnspecified,
			paClipOff,
			&Stream::OpenRecordingStreamCallback,
			static_cast<void*>(&file)
		);

		if (!err)
		{
			active = true;
		}
		return err;
	}

	int Stream::OpenPlaybackStreamCallback(
		const void* inputBuffer, void* outputBuffer,
		unsigned long framesPerBuffer,
		const PaStreamCallbackTimeInfo* timeInfo,
		PaStreamCallbackFlags statusFlags,
		void* userData
	)
	{
		return (static_cast<ReadFile*>(userData)->ReadToBuffer(
			inputBuffer, outputBuffer,
			framesPerBuffer,
			timeInfo,
			statusFlags,
			userData
		));
	}

	int Stream::OpenRecordingStreamCallback(
		const void* inputBuffer, void* outputBuffer,
		unsigned long framesPerBuffer,
		const PaStreamCallbackTimeInfo* timeInfo,
		PaStreamCallbackFlags statusFlags,
		void* userData
	)
	{
		return (static_cast<WriteFile*>(userData)->WriteToBuffer(
			inputBuffer, outputBuffer,
			framesPerBuffer,
			timeInfo,
			statusFlags,
			userData
		));
	}

	Stream::~Stream()
	{
	}
}