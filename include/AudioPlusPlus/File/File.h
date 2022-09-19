#pragma once
#include <AudioPlusPlus/TagHandle/TagHandle.h>
#include <sndfile.hh>

namespace AudioPlusPlus
{
	/**
	 * @brief      Information about an audio file.
	 */
	struct FileData
	{
		std::string path;
		double length;
		int sampleRate;
		int channels;
	};

	/**
	 * @brief      Interface file class for an audio file supported by libsndfile.
	 */
	class IFile : protected SndfileHandle
	{
		public:
			/**
			 * @brief      Constructs a new audio file instance.
			 *
			 * @param[in]  path        The path
			 * @param[in]  mode        The mode
			 * @param[in]  format      The format
			 * @param[in]  channels    The channels
			 * @param[in]  samplerate  The samplerate
			 */
			IFile(const std::string& path, int mode, int format,
				int channels = 2, int samplerate = 44100);

			/**
			 * @brief      Destroys the object.
			 */
			~IFile();

			/**
			 * @brief      Gets the TagLib tag handle.
			 *
			 * @return     The tag handle.
			 */
			const TagHandle* GetTagHandle();

			/**
			 * @brief      Gets the file data.
			 *
			 * @return     The file data.
			 */
			const FileData* GetFileData();

			/**
			 * @brief      Gets the current position, in seconds, of the cursor in the file.
			 *
			 * @return     The position.
			 */
			double GetPosition();

			/**
			 * @brief      Closes the file.
			 *
			 * @return     1 on success else 0.
			 */
			virtual int Close() = 0;

		private:

		protected:
			TagHandle* tag;
			FileData* data;

			bool closed = false;
	};
}