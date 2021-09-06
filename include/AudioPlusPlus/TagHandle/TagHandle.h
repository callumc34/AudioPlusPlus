#pragma once
#pragma warning( disable: 4251 )
#include <taglib/tag.h>
#include <taglib/fileref.h>
#include <taglib/tpropertymap.h>


namespace AudioPlusPlus
{
	class TagHandle : public TagLib::FileRef
	{
		public:
			TagHandle(const std::string& path);
			~TagHandle();

			bool IsValid() const;

			const TagLib::Tag* GetTag() const;
			const TagLib::PropertyMap* GetPropertyMap() const;
			const TagLib::AudioProperties* GetAudioProperties() const;

			//TODO(Callum): Write non const functions for setting tag values

		private:
			bool valid = false;

			TagLib::Tag* fileTag;
			TagLib::PropertyMap properties;
			TagLib::AudioProperties* audioProperties;
	};
}