#include <AudioPlusPlus/File/File.h>
#include <AudioPlusPlus/File/AIFF.h>
#include <AudioPlusPlus/File/WAV.h>
#include <AudioPlusPlus/File/MP3.h>
#include <AudioPlusPlus/Log/Log.h>
#include <filesystem>
#include <algorithm>

namespace AudioPlusPlus
{
	File::File()
	{

	}

	int File::OpenStream(Stream* stream, PaStreamParameters OutputParameters)
	{
		//TODO(Callum): Fix config parameters
		//Also just fix in general
		PaError err = Pa_OpenStream(
			stream->Get(),
			nullptr,
			&OutputParameters,
			44100,
			paFramesPerBufferUnspecified,
			paClipOff,
			&File::AudioCallback,
			nullptr
		);

		return 0;
	}

	const FileData& File::GetFileData()
	{
		return data;
	}

	int File::AudioCallback(
		const void* inputBuffer, void* outputBuffer,
		unsigned long framesPerBuffer,
		const PaStreamCallbackTimeInfo* timeInfo,
		PaStreamCallbackFlags statusFlags,
		void* userData
	)
	{
		return (static_cast<File*>(userData)->FillBuffer(
			inputBuffer, outputBuffer,
			framesPerBuffer,
			timeInfo,
			statusFlags,
			userData
		));
	}

	File* File::Open(const std::string& path)
	{
		if (!VerifyFile(path))
			return nullptr;
		const std::filesystem::path p = path;
		std::string ext = p.extension().string();
		std::transform(ext.begin(), ext.end(), ext.begin(), ::tolower);
		if (ext == ".mp3")
			return new MP3(path);
		else if (ext == ".wav")
			return new WAV(path);
		else if (ext == ".aiff")
			return new AIFF(path);
		else
			return nullptr;
	}

	int File::VerifyFile(const std::string& path)
	{
		const std::filesystem::path p = path;
		return std::filesystem::exists(p);
	}

	File::~File()
	{

	}
}