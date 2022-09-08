#pragma once
#include <AudioPlusPlus/Device/DeviceManager.h>
#include <AudioPlusPlus/File/ReadFile.h>
#include <AudioPlusPlus/File/WriteFile.h>
#include <portaudio.h>

namespace AudioPlusPlus
{
	class Stream
	{
		public:
			struct StreamConfig
			{
				double volume = 1;

				bool seek = false;
				double position = 0;

				bool loop = false;
				double start = 0;
				double end = 0;

				ReadFile* rFile = nullptr;
				WriteFile* wFile = nullptr;
			};

			operator bool() const;

			PaStream** GetBuffer();

			PaError SetDevice(int index);
			PaError SetDevice(const Device& device);
			const Device* GetDevice();

			double SetVolume(double v);
			double GetVolume();

			double SetPosition(double position);
			double GetPosition();

			void SetLoop(double start, double end);
			int StopLoop();

			PaError Start();
			PaError Stop();
			PaError Close();

		private:
			Stream();
			~Stream();

			PaError OpenPlaybackStream(ReadFile& file);
			PaError OpenRecordingStream(WriteFile& file);
			int ReadFromFileCallback(
				const void* inputBuffer, void* outputBuffer,
				unsigned long framesPerBuffer,
				const PaStreamCallbackTimeInfo* timeInfo,
				PaStreamCallbackFlags statusFlags,
				void* userData
			);
			int WriteToFileCallback (
				const void* inputBuffer, void* outputBuffer,
				unsigned long framesPerBuffer,
				const PaStreamCallbackTimeInfo* timeInfo,
				PaStreamCallbackFlags statusFlags,
				void* userData
			);

			PaStream* stream = 0;
			Device* device = nullptr;
			StreamConfig config;
			bool active = false;

			friend int OpenPlaybackStreamCallback(
				const void* inputBuffer, void* outputBuffer,
				unsigned long framesPerBuffer,
				const PaStreamCallbackTimeInfo* timeInfo,
				PaStreamCallbackFlags statusFlags,
				void* userData
			);

			friend  int OpenRecordingStreamCallback(
				const void* inputBuffer, void* outputBuffer,
				unsigned long framesPerBuffer,
				const PaStreamCallbackTimeInfo* timeInfo,
				PaStreamCallbackFlags statusFlags,
				void* userData
			);

			friend class StreamManager;
			friend class Player;
			friend class Recorder;
	};
}