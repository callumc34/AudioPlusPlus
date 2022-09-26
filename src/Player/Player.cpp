#include <AudioPlusPlus/Player/Player.h>

namespace AudioPlusPlus
{
	int Player::Load(IReadFile& file, Stream& stream, const Device& device)
	{
		return stream.OpenPlaybackStream(file);
	}

	Stream* Player::Load(IReadFile& file, const Device& device)
	{
		Stream* stream = StreamManager::Get().NewStream(file.GetFileData().path);
		stream->OpenPlaybackStream(file);
		return stream;
	}

	int Player::Close(Stream* stream)
	{
		return stream->Close();
	}
}