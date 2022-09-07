#include <AudioPlusPlus/AudioPlusPlus.h>

int main(int argc, char** argv)
{
	AudioPlusPlus::Init();
	if (argc < 2)
	{
		AUDIO_ERROR("Please specify a file to play audio from");
		return -1;
	}
	AUDIO_INFO("Hello from AudioPlusPlus");
	AudioPlusPlus::ReadFile file(argv[1]);
	AUDIO_INFO("File path: " + file.GetFileData()->path);
	AUDIO_INFO("File Bitrate: " + std::to_string(file.GetTagHandle()->GetAudioProperties()->bitrate()));
	AUDIO_INFO("File Sample Rate: " + std::to_string(file.GetTagHandle()->GetAudioProperties()->sampleRate()));
	AUDIO_INFO("File Channels: " + std::to_string(file.GetTagHandle()->GetAudioProperties()->channels()));
	AUDIO_INFO("File Length: " + std::to_string(file.GetTagHandle()->GetAudioProperties()->lengthInSeconds()));

	//Play audio
	AUDIO_INFO("Playing from file...");

	AudioPlusPlus::Stream* stream = AudioPlusPlus::Player::Load(file);
	stream->Start();
	AudioPlusPlus::Wait(5);
	AudioPlusPlus::Player::Close(stream);
	return 0;
}