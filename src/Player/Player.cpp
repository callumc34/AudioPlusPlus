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
		if (stream.GetDevice() == nullptr)
		{
			stream.SetDevice(device);
		}

		return stream.OpenPlaybackStream(file);
	}

	int Player::Close(Stream& stream)
	{
		return stream.Close();
	}

	Player::~Player()
	{

	}
}