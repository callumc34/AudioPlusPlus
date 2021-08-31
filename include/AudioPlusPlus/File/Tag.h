#pragma once
#pragma warning( disable: 4251 )
#include <taglib/tag.h>
#include <taglib/fileref.h>
#include <taglib/tpropertymap.h>


namespace AudioPlusPlus
{
	class Tag : public TagLib::FileRef
	{
		public:
			Tag(const std::string& path);
			~Tag();

			bool IsValid();

			TagLib::Tag* GetTag() const;
			const TagLib::PropertyMap& GetPropertyMap() const;
			const TagLib::AudioProperties& GetAudioProperties() const;

		private:
			bool valid = false;

			TagLib::Tag* fileTag;
			TagLib::PropertyMap properties;
			TagLib::AudioProperties* audioProperties;
	};
}