#include <AudioPlusPlus/File/File.h>

namespace AudioPlusPlus
{
	IFile::IFile(const std::string& path, int mode, int format,
		int channels, int samplerate)
		: SndfileHandle(path, mode, format, channels, samplerate)
	{
		tag = new TagHandle(path);
		data = new FileData();
		data->path = path;
	}

	const TagHandle* IFile::GetTagHandle()
	{
		return tag;
	}

	const FileData* IFile::GetFileData()
	{
		return data;
	}

	double IFile::GetPosition()
	{
		return (double)seek(0, SEEK_CUR) / samplerate();
	}

	IFile::~IFile()
	{
		delete tag;
		delete data;
	}
}