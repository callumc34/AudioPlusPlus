#pragma once
#include <portaudio.h>
#include <AudioPlusPlus/Device/DeviceManager.h>
#include <AudioPlusPlus/File/ReadFile.h>
#include <AudioPlusPlus/File/WriteFile.h>

namespace AudioPlusPlus
{
	class Stream
	{
		public:
			operator bool() const;

			PaStream** GetBuffer();

			PaError SetDevice(int index);
			PaError SetDevice(const Device& device);

			const Device* GetDevice();

			PaError Start();
			PaError Stop();
			PaError Close();

			//Callbacks
			static int OpenPlaybackStreamCallback(
				const void* inputBuffer, void* outputBuffer,
				unsigned long framesPerBuffer,
				const PaStreamCallbackTimeInfo* timeInfo,
				PaStreamCallbackFlags statusFlags,
				void* userData
			);

			static int OpenRecordingStreamCallback(
				const void* inputBuffer, void* outputBuffer,
				unsigned long framesPerBuffer,
				const PaStreamCallbackTimeInfo* timeInfo,
				PaStreamCallbackFlags statusFlags,
				void* userData
			);

		private:
			Stream();
			~Stream();

			PaError OpenPlaybackStream(ReadFile& file);
			PaError OpenRecordingStream(WriteFile& file);

			PaStream* stream = 0;
			Device* device = nullptr;
			bool active = false;

			friend class StreamManager;
			friend class Player;
			friend class Recorder;
	};
}