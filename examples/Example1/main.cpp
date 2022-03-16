#include <AudioPlusPlus/AudioPlusPlus.h>

namespace audio = AudioPlusPlus;

int main(int argc, char** argv)
{
	audio::Init();
	if (argc < 2)
	{
		AUDIO_ERROR("Please specify a file to play audio from");
		return -1;
	}
	AUDIO_INFO("Hello from AudioPlusPlus");
	audio::ReadFile file(argv[1]);
	AUDIO_INFO("File path: " + file.GetFileData()->path);
	AUDIO_INFO("File Bitrate: " + std::to_string(file.GetTagHandle()->GetAudioProperties()->bitrate()));
	AUDIO_INFO("File Sample Rate: " + std::to_string(file.GetTagHandle()->GetAudioProperties()->sampleRate()));
	AUDIO_INFO("File Channels: " + std::to_string(file.GetTagHandle()->GetAudioProperties()->channels()));
	AUDIO_INFO("File Length: " + std::to_string(file.GetTagHandle()->GetAudioProperties()->lengthInSeconds()));

	//Play audio
	AUDIO_INFO("Playing from file...");

	audio::Stream* stream = audio::Player::Play(file);
	stream->Start();
	Pa_Sleep(10000);

	return 0;
}