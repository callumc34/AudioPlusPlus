#include <AudioPlusPlus/Player/Player.h>

namespace AudioPlusPlus
{
	Player* Player::instance = nullptr;

	Player& Player::Get()
	{
		if (instance == nullptr)
			instance = new Player();

		return *instance;
	}

	Player::Player()
	{

	}

	int Player::Play(ReadFile& file, Stream& stream, const Device& device)
	{
		return stream.OpenPlaybackStream(file);
	}

	Stream* Player::Play(ReadFile& file, const Device& device)
	{
		Stream* stream = StreamManager::Get().NewStream(file.GetFileData()->path);
		stream->OpenPlaybackStream(file);
		return stream;
	}

	int Player::Close(Stream& stream)
	{
		return stream.Close();
	}

	Player::~Player()
	{

	}
}