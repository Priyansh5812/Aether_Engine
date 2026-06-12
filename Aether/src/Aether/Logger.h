#pragma once
#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include <memory>
namespace Aether
{
	class AE_API Logger
	{
		public:
			Logger(const Logger&&) = delete;
			Logger(std::string&& name);
			~Logger();
		public:
			template<typename ... Args>
			void Log_Internal(spdlog::level::level_enum lvl, spdlog::format_string_t<Args...> fmt, Args&&... args)
			{
				_logger->log(
					spdlog::source_loc{ __FILE__, __LINE__, SPDLOG_FUNCTION },
					lvl,
					fmt,
					std::forward<Args>(args)...
				);
			}
		private:
			std::shared_ptr <spdlog::logger> _logger;
			std::shared_ptr <spdlog::sinks::stdout_color_sink_mt> _sink;
		private:
			void Initialize(std::string&& name);
			void Release();
	};
}

