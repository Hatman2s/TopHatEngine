#include "Log.h"
#include "spdlog/sinks/stdout_color_sinks.h"
namespace TopHat
{
	std::shared_ptr<spdlog::logger> Log::m_EngineLog;
	std::shared_ptr<spdlog::logger> Log::m_ApplicationLog;

	void Log::init()
	{
		spdlog::set_pattern("%^[%T] %n:%v. %@%$ ");
		
		m_EngineLog = spdlog::stdout_color_mt("TOP HAT ENGINE");
		m_EngineLog->set_level(spdlog::level::trace);

		m_ApplicationLog = spdlog::stdout_color_mt("APP");
		m_ApplicationLog->set_level(spdlog::level::trace);

	}
}

