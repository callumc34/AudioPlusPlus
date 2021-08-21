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

	int Player::Open(Stream* stream, PaStreamParameters OutputParameters)
	{
		this->stream = stream;
		DataStream = stream->Get();

		//TODO(Callum): Fix config parameters
		//Also just fix in general
		PaError err = Pa_OpenStream(
			&DataStream,
			nullptr,
			&OutputParameters,
			44100,
			paFramesPerBufferUnspecified,
			paClipOff,
			nullptr,
			nullptr
		);
		return 0;
	}

	Player::~Player()
	{

	}
}