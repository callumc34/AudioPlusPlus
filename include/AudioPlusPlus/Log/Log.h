#pragma once
#ifdef ENABLE_LOGGING
#include <memory>

// This ignores all warnings raised inside External headers
#pragma warning(push, 0)
#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>
#pragma warning(pop)

namespace AudioPlusPlus {
	class Log
	{
		public:
			static void Init();

			static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return CoreLogger; }
			static std::shared_ptr<spdlog::logger>& GetClientLogger() { return ClientLogger; }

		private:
			static std::shared_ptr<spdlog::logger> CoreLogger;
			static std::shared_ptr<spdlog::logger> ClientLogger;

	};
}
//Core log macros for the library
#define AUDIO_CORE_TRACE(...) ::AudioPlusPlus::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define AUDIO_CORE_INFO(...) ::AudioPlusPlus::Log::GetCoreLogger()->info(__VA_ARGS__)
#define AUDIO_CORE_WARN(...) ::AudioPlusPlus::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define AUDIO_CORE_ERROR(...) ::AudioPlusPlus::Log::GetCoreLogger()->error(__VA_ARGS__)
#define AUDIO_CORE_CRITICAL(...) ::AudioPlusPlus::Log::GetCoreLogger()->critical(__VA_ARGS__)

//Client log macros

#define AUDIO_TRACE(...) ::AudioPlusPlus::Log::GetClientLogger()->trace(__VA_ARGS__)
#define AUDIO_INFO(...) ::AudioPlusPlus::Log::GetClientLogger()->info(__VA_ARGS__)
#define AUDIO_WARN(...) ::AudioPlusPlus::Log::GetClientLogger()->warn(__VA_ARGS__)
#define AUDIO_ERROR(...) ::AudioPlusPlus::Log::GetClientLogger()->error(__VA_ARGS__)
#define AUDIO_CRITICAL(...) ::AudioPlusPlus::Log::GetClientLogger()->critical(__VA_ARGS__)
#else
//Core log macros for the library
#define AUDIO_CORE_TRACE(...) 
#define AUDIO_CORE_INFO(...) 
#define AUDIO_CORE_WARN(...) 
#define AUDIO_CORE_ERROR(...) 
#define AUDIO_CORE_CRITICAL(...) 

//Client log macros

#define AUDIO_TRACE(...) 
#define AUDIO_INFO(...) 
#define AUDIO_WARN(...) 
#define AUDIO_ERROR(...) 
#define AUDIO_CRITICAL(...) 

namespace AudioPlusPlus
{
	namespace Log
	{
		void Init();
	}
}

#endif