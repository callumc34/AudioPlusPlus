#pragma once
#include <AudioPlusPlus/TagHandle/TagHandle.h>
#include <sndfile.hh>

namespace AudioPlusPlus
{
	struct FileData
	{
		std::string path;
		double length;
		int sampleRate;
		int channels;
	};

	class IFile : protected SndfileHandle
	{
		public:
			IFile(const std::string& path, int mode, int format,
				int channels = 2, int samplerate = 44100);
			~IFile();

			const TagHandle* GetTagHandle();
			const FileData* GetFileData();

			virtual int Close() = 0;

		private:

		protected:
			TagHandle* tag;
			FileData* data;

			bool closed = false;
	};
}