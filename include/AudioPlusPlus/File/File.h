#pragma once
#include <AudioPlusPlus/File/Tag.h>
#include <AudioPlusPlus/Player/Stream.h>
#ifdef _WIN32
#include <windows.h>
#define ENABLE_SNDFILE_WINDOWS_PROTOTYPES 1
#endif
#include <sndfile.hh>
#include <portaudio.h>

namespace AudioPlusPlus
{
	enum class FileFormat
	{
		Error,
		NotLoaded,
		Unsupported,
		AIFF,
		Wave,
		MP3
	};

	struct FileData
	{
		std::string path;
		FileFormat format;
		int length;
		int sampleRate;
		int bitDepth;
		int channels;
	};

	class File : private SndfileHandle
	{
		public:
			File(const std::string& path);
			~File();

			const Tag tag;

			const FileData& GetFileData();

			int FillBuffer(
				const void* inputBuffer, void* outputBuffer,
				unsigned long framesPerBuffer,
				const PaStreamCallbackTimeInfo* timeInfo,
				PaStreamCallbackFlags statusFlags,
				void* userData
			);

			static int AudioCallback(
				const void* inputBuffer, void* outputBuffer,
				unsigned long framesPerBuffer,
				const PaStreamCallbackTimeInfo* timeInfo,
				PaStreamCallbackFlags statusFlags,
				void* userData
			);

		private:
			int OpenStream(Stream* stream, PaStreamParameters OutputParameters);
			friend class Player;

		protected:
			FileData data;
	};
}