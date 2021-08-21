#include <AudioPlusPlus/Config/Config.h>

namespace AudioPlusPlus
{
	Config* Config::instance = nullptr;

	Config::Config()
	{

	}

	Config& Config::Get()
	{
		if (instance == nullptr)
			instance = new Config();

		return *instance;
	}

	Config::~Config()
	{

	}
}