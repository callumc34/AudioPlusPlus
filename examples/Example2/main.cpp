#include <AudioPlusPlus/AudioPlusPlus.h>

namespace audio = AudioPlusPlus;

int main(int argc, char** argv)
{
	audio::Init();
	if (argc < 2)
	{
		AUDIO_ERROR("Please specify a file to write to");
		return -1;
	}
	AUDIO_INFO("Hello from AudioPlusPlus");
	AUDIO_INFO("Recording to file: " + std::string(argv[1]));


	audio::WriteFile file(argv[1]);


	audio::Stream* stream = audio::Recorder::Record(file);
	stream->Start();
	Pa_Sleep(5000);
	audio::Recorder::Close(*stream);
	return 0;
}