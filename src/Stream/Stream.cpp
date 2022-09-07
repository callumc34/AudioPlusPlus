#include <AudioPlusPlus/Stream/Stream.h>
#include <functional>

namespace AudioPlusPlus
{
	Stream::Stream()
	{

	}

	Stream::operator bool() const
	{
		return stream != 0;
	}

	PaStream** Stream::GetBuffer()
	{
		return &stream;
	}

	PaError Stream::SetDevice(int index)
	{
		this->device = DeviceManager::Get().devices[index];
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

	double Stream::SetVolume(double volume)
	{
		config.volume = volume;
		return config.volume;
	}

	double Stream::GetVolume()
	{
		return config.volume;
	}

	double Stream::SetPosition(double position)
	{
		config.seek = true;

		// Get samplerate
		const PaStreamInfo* info = Pa_GetStreamInfo(stream);

		// Seek skips n frames
		config.position = (double)position * info->sampleRate;
		return 0;
	}

	double Stream::GetPosition()
	{
		if (config.rFile != nullptr) return config.rFile->GetPosition();
		if (config.wFile != nullptr) return config.wFile->GetPosition();
		return -1;
	}

	PaError Stream::Start()
	{
		if (stream == 0)
			return paNotInitialized;

		if (Pa_IsStreamActive(stream))
			return paStreamIsNotStopped;

		PaError err = Pa_StartStream(stream);

		return err;
	}

	PaError Stream::Stop()
	{
		if (stream == 0)
			return paNotInitialized;

		if (Pa_IsStreamStopped(stream))
			return paStreamIsStopped;

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

	PaError Stream::OpenPlaybackStream(ReadFile& file)
	{
		if (stream != 0)
		{
			return paStreamIsNotStopped;
		}

		if (device == nullptr)
		{
			SetDevice(DeviceManager::Get().GetDefaultOutputDevice());
		}

		PaStreamParameters OutputParameters{
			device->GetIndex(),
			file.GetFileData()->channels,
			paFloat32,
			device->GetInfo()->defaultLowOutputLatency,
			NULL
		};

		config.rFile = &file;

		int err = Pa_OpenStream(
			&stream,
			nullptr,
			&OutputParameters,
			file.GetFileData()->sampleRate,
			paFramesPerBufferUnspecified,
			paClipOff,
			&OpenPlaybackStreamCallback,
			static_cast<void*>(this)
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
		if (device == nullptr)
		{
			SetDevice(DeviceManager::Get().GetDefaultInputDevice());
		}

		PaStreamParameters InputParameters{
			device->GetIndex(),
			device->GetInfo()->maxInputChannels,
			paFloat32,
			device->GetInfo()->defaultLowInputLatency,
			NULL
		};

		config.wFile = &file;

		int err = Pa_OpenStream(
			&stream,
			&InputParameters,
			nullptr,
			file.GetFileData()->sampleRate,
			paFramesPerBufferUnspecified,
			paClipOff,
			&OpenRecordingStreamCallback,
			static_cast<void*>(this)
		);

		if (!err)
		{
			active = true;
		}
		return err;
	}

	int Stream::ReadFromFileCallback(
		const void* inputBuffer, void* outputBuffer,
		unsigned long framesPerBuffer,
		const PaStreamCallbackTimeInfo* timeInfo,
		PaStreamCallbackFlags statusFlags,
		void* userData
	)
	{
		return config.rFile->ReadToBuffer(
			inputBuffer, outputBuffer,
			framesPerBuffer,
			timeInfo,
			statusFlags,
			static_cast<void*>(&config)
		);
	}

	int Stream::WriteToFileCallback(
		const void* inputBuffer, void* outputBuffer,
		unsigned long framesPerBuffer,
		const PaStreamCallbackTimeInfo* timeInfo,
		PaStreamCallbackFlags statusFlags,
		void* userData
	)
	{
		return config.wFile->WriteToBuffer(
			inputBuffer, outputBuffer,
			framesPerBuffer,
			timeInfo,
			statusFlags,
			static_cast<void*>(&config)
		);
	}

	Stream::~Stream()
	{
	}

	static int OpenPlaybackStreamCallback(
		const void* inputBuffer, void* outputBuffer,
		unsigned long framesPerBuffer,
		const PaStreamCallbackTimeInfo* timeInfo,
		PaStreamCallbackFlags statusFlags,
		void* userData
	)
	{
		return static_cast<Stream*>(userData)->ReadFromFileCallback(
			inputBuffer, outputBuffer,
			framesPerBuffer,
			timeInfo,
			statusFlags,
			nullptr
		);
	}

	static int OpenRecordingStreamCallback(
		const void* inputBuffer, void* outputBuffer,
		unsigned long framesPerBuffer,
		const PaStreamCallbackTimeInfo* timeInfo,
		PaStreamCallbackFlags statusFlags,
		void* userData
	)
	{
		return static_cast<Stream*>(userData)->WriteToFileCallback(
			inputBuffer, outputBuffer,
			framesPerBuffer,
			timeInfo,
			statusFlags,
			nullptr
		);
	}
}