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

	int Player::Play(File* file, Stream* stream, Device* device)
	{
		if (device == nullptr)
			device = new Device(Pa_GetDefaultOutputDevice());

		PaStreamParameters OutputParameters{
			device->GetIndex(),
			file->GetFileData().channels,
			paFloat32,
			device->GetInfo()->defaultLowOutputLatency,
			NULL
		};

		return file->OpenStream(stream, OutputParameters);
	}

	Player::~Player()
	{

	}
}