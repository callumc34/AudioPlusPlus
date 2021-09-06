#include <AudioPlusPlus/Recorder/Recorder.h>

namespace AudioPlusPlus
{
	Recorder* Recorder::instance = nullptr;

	Recorder& Recorder::Get()
	{
		if (instance == nullptr)
			instance = new Recorder();

		return *instance;
	}

	Recorder::Recorder()
	{

	}

	int Recorder::Record(WriteFile& file, Stream& stream,
		const Device& device)
	{
		if (stream.GetDevice() == nullptr)
		{
			stream.SetDevice(device);
		}

		return stream.OpenRecordingStream(file);
	}

	int Recorder::Close(Stream& stream)
	{
		return stream.Close();
	}

	Recorder::~Recorder()
	{

	}
}