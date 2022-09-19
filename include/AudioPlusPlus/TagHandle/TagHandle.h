#pragma once
#pragma warning( disable: 4251 )
#include <taglib/tag.h>
#include <taglib/fileref.h>
#include <taglib/tpropertymap.h>


namespace AudioPlusPlus
{
	/**
	 * @brief      Class to interact with TagLib properties of a file.
	 */
	class TagHandle : public TagLib::FileRef
	{
		public:
			/**
			 * @brief      Constructs a new TagHandle for a file.
			 *
			 * @param[in]  path  The path of the file.
			 */
			TagHandle(const std::string& path);
			~TagHandle();

			/**
			 * @brief      Determines if the tags are valid.
			 *
			 * @return     True if valid, False otherwise.
			 */
			bool IsValid() const;

			/**
			 * @brief      Gets the TagLib tags.
			 *
			 * @return     The tags.
			 */
			const TagLib::Tag* GetTag() const;

			/**
			 * @brief      Gets the property map of the file.
			 *
			 * @return     The property map.
			 */
			const TagLib::PropertyMap* GetPropertyMap() const;

			/**
			 * @brief      Gets the audio properties of the file.
			 *
			 * @return     The audio properties.
			 */
			const TagLib::AudioProperties* GetAudioProperties() const;

			//TODO(Callum): Write non const functions for setting tag values

		private:
			bool valid = false;

			TagLib::Tag* fileTag;
			TagLib::PropertyMap properties;
			TagLib::AudioProperties* audioProperties;
	};
}