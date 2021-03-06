#include <AudioPlusPlus/AudioPlusPlus.h>

int main(int argc, char** argv)
{
	AudioPlusPlus::Init();
	if (argc < 2)
	{
		AUDIO_ERROR("Please specify a file to write to");
		return -1;
	}
	AUDIO_INFO("Hello from AudioPlusPlus");
	AUDIO_INFO("Recording to file: " + std::string(argv[1]));


	AudioPlusPlus::WriteFile file(argv[1]);


	AudioPlusPlus::Stream* stream = AudioPlusPlus::Recorder::Record(file);
	stream->Start();
	Pa_Sleep(5000);
	AudioPlusPlus::Recorder::Close(stream);
	return 0;
}