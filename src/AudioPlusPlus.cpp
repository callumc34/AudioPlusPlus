#include <AudioPlusPlus/AudioPlusPlus.h>
#include <portaudio.h>

namespace AudioPlusPlus
{
	int Init()
	{
		Log::Init();
		AUDIO_CORE_INFO("Initialising Port Audio");
		PaError err = Pa_Initialize();
		if (err != paNoError)
		{
			AUDIO_CORE_ERROR(Pa_GetErrorText(err));
			return -1;
		}
		AUDIO_CORE_INFO("Successfully initialised Port Audio. Version: " + std::string(Pa_GetVersionInfo()->versionText));
		return 0;
	}

	int Exit()
	{
		AUDIO_CORE_INFO("Shutting down Port Audio");
		PaError err = Pa_Terminate();
		if (err != paNoError) 
		{
			AUDIO_CORE_ERROR(Pa_GetErrorText(err));
			return -1;
		}
		AUDIO_CORE_INFO("Successfully shut down Port Audio");
		return 0;
	}
}