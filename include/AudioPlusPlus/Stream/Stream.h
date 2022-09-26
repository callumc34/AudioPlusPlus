#pragma once
#include <AudioPlusPlus/Device/DeviceManager.h>
#include <AudioPlusPlus/File/ReadFile.h>
#include <AudioPlusPlus/File/WriteFile.h>
#include <portaudio.h>

namespace AudioPlusPlus
{
	/**
	 * @brief      Class to interact with portaudio's stream.
	 * 
	 * Contains the IO methods for AudioPlusPlus.
	 */
	class Stream
	{
		public:
			/**
			 * @brief      Configuration options for the Stream.
			 */
			struct StreamConfig
			{
				double volume = 1;

				bool seek = false;
				double position = 0;

				bool loop = false;
				double start = 0;
				double end = 0;

				IReadFile* rFile = nullptr;
				IWriteFile* wFile = nullptr;
			};

			/**
			 * @brief      Check if Stream is not null.
			 */
			operator bool() const;

			/**
			 * @brief      Gets the portaudio stream buffer.
			 *
			 * @return     The buffer.
			 */
			PaStream** GetBuffer();

			/**
			 * @brief      Sets the Device of the stream.
			 *
			 * @param[in]  index  The index of the Device in DeviceManager.
			 *
			 * @return     The pa error code.
			 */
			PaError SetDevice(int index);

			/**
			 * @brief      Sets the Device of the stream.
			 *
			 * @param[in]  device  The Device.
			 *
			 * @return     The pa error code.
			 */
			PaError SetDevice(const Device& device);

			/**
			 * @brief      Gets the current Device the stream is using.
			 *
			 * @return     The Device.
			 */
			const Device* GetDevice();

			/**
			 * @brief      Set the volume of the Stream.
			 *
			 * @param[in]  v     The new value
			 *
			 * @return     Returns the new volume of the Stream.
			 */
			double SetVolume(double v);

			/**
			 * @brief      Gets the volume of the Stream.
			 *
			 * @return     The volume.
			 */
			double GetVolume();

			/**
			 * @brief      Set position in the file to read, in seconds.
			 *
			 * @param[in]  position  The position, in seconds.
			 *
			 * @return     The new position in the Stream.
			 */
			double SetPosition(double position);

			/**
			 * @brief      Gets the position of the Stream in the file in seconds.
			 *
			 * @return     The position, in seconds.
			 */
			double GetPosition();

			/**
			 * @brief      Sets whether to loop the file at the specified period, in seconds.
			 *
			 * @param[in]  start  The start of the loop.
			 * @param[in]  end    The end of the loop.
			 */
			void SetLoop(double start, double end);

			/**
			 * @brief      Stops a loop.
			 *
			 * @return     Error code.
			 */
			int StopLoop();

			/**
			 * @brief      Starts the Stream.
			 *
			 * @return     The pa error code.
			 */
			PaError Start();

			/**
			 * @brief      Stops/pauses the Stream.
			 *
			 * @return     The pa error code.
			 */
			PaError Stop();

			/**
			 * @brief      Closes the Stream.
			 *
			 * @return     The pa error code.
			 */
			PaError Close();

		private:
			/**
			 * @brief      Constructs a new Stream.
			 */
			Stream();

			/**
			 * @brief      Destroys the Stream.
			 */
			~Stream();

			/**
			 * @brief      Opens a playback Stream.
			 *
			 * @param      file  The IReadFile to use.
			 *
			 * @return     The pa error code.
			 */
			PaError OpenPlaybackStream(IReadFile& file);

			/**
			 * @brief      Opens a recording Stream.
			 *
			 * @param      file  The IWriteFile to use.
			 *
			 * @return     The pa error code.
			 */
			PaError OpenRecordingStream(IWriteFile& file);

			/**
			 * @brief      Callback function for portaudio to begin audio playback.
			 *
			 * @param[in]  inputBuffer      The input buffer
			 * @param      outputBuffer     The output buffer
			 * @param[in]  framesPerBuffer  The frames per buffer
			 * @param[in]  timeInfo         The time information
			 * @param[in]  statusFlags      The status flags
			 * @param      userData         The user data
			 *
			 * @return     Error code.
			 */
			int ReadFromFileCallback(
				const void* inputBuffer, void* outputBuffer,
				unsigned long framesPerBuffer,
				const PaStreamCallbackTimeInfo* timeInfo,
				PaStreamCallbackFlags statusFlags,
				void* userData
			);

			/**
			 * @brief      Callback function for portaudio to begin audio recording.
			 *
			 * @param[in]  inputBuffer      The input buffer
			 * @param      outputBuffer     The output buffer
			 * @param[in]  framesPerBuffer  The frames per buffer
			 * @param[in]  timeInfo         The time information
			 * @param[in]  statusFlags      The status flags
			 * @param      userData         The user data
			 *
			 * @return     Error code.
			 */
			int WriteToFileCallback (
				const void* inputBuffer, void* outputBuffer,
				unsigned long framesPerBuffer,
				const PaStreamCallbackTimeInfo* timeInfo,
				PaStreamCallbackFlags statusFlags,
				void* userData
			);

			/** The internal stream */
			PaStream* stream = 0;

			/** Current Device */
			Device* device = nullptr;

			/** Current StreamConfig in use. */
			StreamConfig config;

			/** If the Stream is active. */
			bool active = false;

			/**
			 * @brief      Callback function for portaudio to begin audio playback.
			 *
			 * @param[in]  inputBuffer      The input buffer
			 * @param      outputBuffer     The output buffer
			 * @param[in]  framesPerBuffer  The frames per buffer
			 * @param[in]  timeInfo         The time information
			 * @param[in]  statusFlags      The status flags
			 * @param      userData         The user data
			 *
			 * @return     Error code.
			 */
			friend int OpenPlaybackStreamCallback(
				const void* inputBuffer, void* outputBuffer,
				unsigned long framesPerBuffer,
				const PaStreamCallbackTimeInfo* timeInfo,
				PaStreamCallbackFlags statusFlags,
				void* userData
			);


			/**
			 * @brief      Callback function for portaudio to begin audio recording.
			 *
			 * @param[in]  inputBuffer      The input buffer
			 * @param      outputBuffer     The output buffer
			 * @param[in]  framesPerBuffer  The frames per buffer
			 * @param[in]  timeInfo         The time information
			 * @param[in]  statusFlags      The status flags
			 * @param      userData         The user data
			 *
			 * @return     Error code.
			 */
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