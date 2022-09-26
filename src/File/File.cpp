#include <AudioPlusPlus/File/File.h>

namespace AudioPlusPlus
{
	IFile::IFile(const std::string& path)
		: tag(path)
	{
		data = FileData();
		data.path = path;
	}

	const TagHandle& IFile::GetTagHandle()
	{
		return tag;
	}

	const FileData& IFile::GetFileData()
	{
		return data;
	}

	IFile::~IFile()
	{
	}
}