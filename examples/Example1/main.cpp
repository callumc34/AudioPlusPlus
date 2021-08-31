#include <AudioPlusPlus/AudioPlusPlus.h>
#include <AudioPlusPlus/Player/Player.h>
#include <AudioPlusPlus/File/File.h>

using namespace AudioPlusPlus;

int main(int argc, char** argv)
{
	Init();
	if (argc < 2)
	{
		AUDIO_ERROR("Please specify a file to play audio from");
		return -1;
	}
	AUDIO_INFO("Hello from AudioPlusPlus");
	File* x = new File(argv[1]);
	AUDIO_INFO("File path: " + x->GetFileData().path);
	AUDIO_INFO("File Bitrate: " + std::to_string(x->tag.GetAudioProperties().bitrate()));
	AUDIO_INFO("File Sample Rate: " + std::to_string(x->tag.GetAudioProperties().sampleRate()));
	AUDIO_INFO("File Channels: " + std::to_string(x->tag.GetAudioProperties().channels()));
	AUDIO_INFO("File Length: " + std::to_string(x->tag.GetAudioProperties().lengthInSeconds ()));

	//Make a stream
	Stream stream;

	//Play audio
	AUDIO_INFO("Playing from file...");
	Player::Get().Play(x, &stream);
	stream.Start();
	Pa_Sleep(10000);

	return 0;
}