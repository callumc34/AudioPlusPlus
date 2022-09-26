#pragma once
#include <AudioPlusPlus/TagHandle/TagHandle.h>

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
	class IFile
	{
		public:
			/**
			 * @brief      Constructs a new audio file instance.
			 *
			 * @param[in]  path        The path.
			 */
			IFile(const std::string& path);

			/**
			 * @brief      Destroys the object.
			 */
			~IFile();

			/**
			 * @brief      Gets the TagLib TagHandle.
			 *
			 * @return     The tag handle.
			 */
			const TagHandle& GetTagHandle();

			/**
			 * @brief      Gets the FileData.
			 *
			 * @return     The file data.
			 */
			const FileData& GetFileData();

			/**
			 * @brief      Gets the current position, in seconds, of the cursor in the file.
			 *
			 * @return     The position.
			 */
			virtual double GetPosition() = 0;

			/**
			 * @brief      Closes the file.
			 *
			 * @return     1 on success else 0.
			 */
			virtual int Close() = 0;

		protected:
			/** TagHandle of the file */
			TagHandle tag;

			/** File information */
			FileData data;
	};
}