#include <AudioPlusPlus/AudioPlusPlus.h>
#include <AudioPlusPlus/Files.h>

using namespace AudioPlusPlus;

int main(int argc, char** argv)
{
	Init();
	AUDIO_INFO("Hello from AudioPlusPlus");
	File* x = File::Open(argv[1]);
	AUDIO_INFO("File path: " + x->GetFileData().path);
	AUDIO_INFO("File type: " + std::to_string((int)x->GetFileData().format));
	return 0;
}