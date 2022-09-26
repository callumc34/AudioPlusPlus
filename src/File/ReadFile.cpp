#include <AudioPlusPlus/File/ReadFile.h>

namespace AudioPlusPlus
{
	IReadFile::IReadFile(const std::string& path)
		: IFile(path)
	{

	}

	IReadFile::~IReadFile()
	{

	}
}