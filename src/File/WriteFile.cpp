#include <AudioPlusPlus/File/WriteFile.h>
#include <AudioPlusPlus/Log/Log.h>

namespace AudioPlusPlus
{
	IWriteFile::IWriteFile(const std::string& path)
		: IFile(path)
	{
	}

	IWriteFile::~IWriteFile()
	{

	}
}