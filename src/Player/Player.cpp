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

	Player::~Player()
	{

	}
}