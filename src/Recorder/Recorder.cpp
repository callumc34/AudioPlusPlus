#include <AudioPlusPlus/Recorder/Recorder.h>

namespace AudioPlusPlus
{
	int Recorder::Load(IWriteFile& file, Stream& stream,
		const Device& device)
	{
		return stream.OpenRecordingStream(file);
	}

	Stream* Recorder::Load(IWriteFile& file, const Device& device)
	{
		Stream* stream = StreamManager::Get().NewStream(file.GetFileData().path);
		stream->OpenRecordingStream(file);
		return stream;
	}

	int Recorder::Close(Stream* stream)
	{
		return stream->Close();
	}
}