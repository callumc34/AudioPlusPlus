#include <AudioPlusPlus/File/Tag.h>

namespace AudioPlusPlus
{
	Tag::Tag(const std::string& path)
		: TagLib::FileRef(path.c_str())
	{
		if (!isNull())
			valid = true;

		fileTag = tag();
		properties = file()->properties();
		audioProperties = file()->audioProperties();
	}

	TagLib::Tag* Tag::GetTag() const
	{
		return fileTag;
	}

	const TagLib::PropertyMap& Tag::GetPropertyMap() const
	{
		return properties;
	}

	const TagLib::AudioProperties& Tag::GetAudioProperties() const
	{
		return *audioProperties;
	}

	bool Tag::IsValid()
	{
		return valid;
	}

	Tag::~Tag()
	{

	}
}