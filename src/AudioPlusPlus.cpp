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

	// Credit: https://blat-blatnik.github.io/computerBear/making-accurate-sleep-function/
	void Wait(double seconds)
	{
		using namespace std;
		using namespace std::chrono;

		static double estimate = 5e-3;
		static double mean = 5e-3;
		static double m2 = 0;
		static int64_t count = 1;

		while (seconds > estimate)
		{
			auto start = high_resolution_clock::now();
			this_thread::sleep_for(milliseconds(1));
			auto end = high_resolution_clock::now();

			double observed = (end - start).count() / 1e9;
			seconds -= observed;

			++count;
			double delta = observed - mean;
			mean += delta / count;
			m2 += delta * (observed - mean);
			double stddev = sqrt(m2 / (count - 1));
			estimate = mean + stddev;
		}

		// spin lock
		auto start = high_resolution_clock::now();
		while ((high_resolution_clock::now() - start).count() / 1e9 < seconds);
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