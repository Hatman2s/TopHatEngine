#pragma once

 
#include "Handler.h"
#include "spdlog/spdlog.h"
#include <spdlog/fmt/ostr.h>
namespace TopHat
{
	class TOP_HAT_API Log
	{
	public:

		static void init();

		inline static std::shared_ptr<spdlog::logger>& GetEngineLogger() { return m_EngineLog; }
		inline static std::shared_ptr<spdlog::logger>& GetApplicationLogger() { return m_ApplicationLog;}
	private:
		static std::shared_ptr<spdlog::logger> m_EngineLog;
		static std::shared_ptr<spdlog::logger> m_ApplicationLog;

	};

}

#define TH_ENGINE_ERROR(...) ::TopHat::Log::GetEngineLogger()->error(__VA_ARGS__)
#define TH_ENGINE_WARN(...)  ::TopHat::Log::GetEngineLogger()->warn(__VA_ARGS__)
#define TH_ENGINE_INFO(...)  ::TopHat::Log::GetEngineLogger()->info(__VA_ARGS__)
#define TH_ENGINE_TRACE(...) ::TopHat::Log::GetEngineLogger()->trace(__VA_ARGS__)

#define APPLICATION_ERROR(...) ::TopHat::Log::GetApplicationLogger()->error(__VA_ARGS__)
#define APPLICATION_WARN(...)  ::TopHat::Log::GetApplicationLogger()->warn(__VA_ARGS__)
#define APPLICATION_INFO(...)  ::TopHat::Log::GetApplicationLogger()->info(__VA_ARGS__)
#define APPLICATION_TRACE(...) ::TopHat::Log::GetApplicationLogger()->trace(__VA_ARGS__)

