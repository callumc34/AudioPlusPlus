#pragma once
#include <AudioPlusPlus/Stream/Stream.h>
#include <unordered_map>

namespace AudioPlusPlus
{
	class StreamManager
	{
		public:
			StreamManager(StreamManager const&) = delete;
			void operator=(StreamManager const&) = delete;
			static StreamManager& Get();

			Stream* GetStream(const std::string& name);
			Stream* NewStream(const std::string& name);
			int DeleteStream(const std::string& name);
			int DeleteStream(Stream* stream);

		private:
			StreamManager();
			~StreamManager();

			std::unordered_map<std::string, Stream*> streams;
	};
}