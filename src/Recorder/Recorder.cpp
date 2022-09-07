#include <AudioPlusPlus/Recorder/Recorder.h>

namespace AudioPlusPlus
{
	int Recorder::Load(WriteFile& file, Stream& stream,
		const Device& device)
	{
		return stream.OpenRecordingStream(file);
	}

	Stream* Recorder::Load(WriteFile& file, const Device& device)
	{
		Stream* stream = StreamManager::Get().NewStream(file.GetFileData()->path);
		stream->OpenRecordingStream(file);
		return stream;
	}

	int Recorder::Close(Stream* stream)
	{
		return stream->Close();
	}
}