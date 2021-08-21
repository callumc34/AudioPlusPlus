#pragma once
#include <string>

namespace AudioPlusPlus
{
	enum class FileFormat
	{
		Error,
		NotLoaded,
		Unsupported,
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

			const FileData& GetFileData();

		private:

		protected:
			FileData data;
	};
}