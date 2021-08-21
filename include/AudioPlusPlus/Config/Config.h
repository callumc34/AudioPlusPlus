#pragma once

namespace AudioPlusPlus
{
	class Config
	{
		public:
			static Config& Get();

		private:
			static Config* instance;

			Config();
			~Config();

	};
}