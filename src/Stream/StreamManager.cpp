#include <AudioPlusPlus/Stream/StreamManager.h>

namespace AudioPlusPlus
{
	StreamManager* StreamManager::instance = nullptr;

	StreamManager& StreamManager::Get()
	{
		if (instance == nullptr)
			instance = new StreamManager();

		return *instance;
	}

	StreamManager::StreamManager()
	{

	}

	Stream* StreamManager::GetStream(const std::string& name)
	{
		if (streams.count(name) > 0)
		{
			return streams[name];
		}
		return nullptr;
	}

	Stream* StreamManager::NewStream(const std::string& name)
	{
		if (streams.count(name) > 0)
		{
			return streams[name];
		}
		streams[name] = new Stream();
		return streams[name];
	}

	int StreamManager::DeleteStream(const std::string& name)
	{
		return (int)streams.erase(name);
	}

	int StreamManager::DeleteStream(Stream* stream)
	{
		std::string name;
		for (auto& s : streams)
		{
			if (stream == s.second)
			{
				name = s.first;
				break;
			}
		}
		if (name.empty())
		{
			return 0;
		}
		streams.erase(name);
		return 1;
	}

	StreamManager::~StreamManager()
	{

	}
}