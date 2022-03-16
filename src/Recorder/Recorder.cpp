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
		return stream.OpenRecordingStream(file);
	}

	Stream* Recorder::Record(WriteFile& file, const Device& device)
	{
		Stream* stream = StreamManager::Get().NewStream(file.GetFileData()->path);
		stream->OpenRecordingStream(file);
		return stream;
	}

	int Recorder::Close(Stream& stream)
	{
		return stream.Close();
	}

	Recorder::~Recorder()
	{

	}
}