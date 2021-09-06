#include <AudioPlusPlus/TagHandle/TagHandle.h>

namespace AudioPlusPlus
{
	TagHandle::TagHandle(const std::string& path)
		: TagLib::FileRef(path.c_str())
	{
		if (!isNull())
			valid = true;

		fileTag = tag();
		properties = file()->properties();
		audioProperties = file()->audioProperties();
	}

	const TagLib::Tag* TagHandle::GetTag() const
	{
		return fileTag;
	}

	const TagLib::PropertyMap* TagHandle::GetPropertyMap() const
	{
		return &properties;
	}

	const TagLib::AudioProperties* TagHandle::GetAudioProperties() const
	{
		return audioProperties;
	}

	bool TagHandle::IsValid() const
	{
		return valid;
	}

	TagHandle::~TagHandle()
	{

	}
}