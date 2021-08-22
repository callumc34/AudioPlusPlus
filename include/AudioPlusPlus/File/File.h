#pragma once
#include <AudioPlusPlus/Player/Stream.h>
#include <portaudio.h>
#include <string>
#include <functional>

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
		FileFormat format;
		int length;
		std::string path;
	};

	class File
	{
		public:
			File();
			~File();

			int OpenStream(Stream* stream, PaStreamParameters OutputParameters);

			const FileData& GetFileData();

			virtual int FillBuffer(
				const void* inputBuffer, void* outputBuffer,
				unsigned long framesPerBuffer,
				const PaStreamCallbackTimeInfo* timeInfo,
				PaStreamCallbackFlags statusFlags,
				void* userData
			) = 0;

			static int AudioCallback(
				const void* inputBuffer, void* outputBuffer,
				unsigned long framesPerBuffer,
				const PaStreamCallbackTimeInfo* timeInfo,
				PaStreamCallbackFlags statusFlags,
				void* userData
			);

			static File* Open(const std::string& path);
			static int VerifyFile(const std::string& path);

		private:

		protected:
			FileData data;
	};
}