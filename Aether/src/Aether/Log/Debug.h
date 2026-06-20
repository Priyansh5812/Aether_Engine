#pragma once
#include "Logger.h"

namespace Aether
{
	class AE_API Debug
	{
		private:
			Debug() = delete;
			~Debug() = delete;
		public:
			static void Init();
			static void Dispose();
			template <typename... Args>
			inline static void Log(spdlog::format_string_t<Args...> fmt, Args&&... args)
			{
				if (!_logger)
					return;

				_logger->Log_Internal(spdlog::level::level_enum::info, fmt, std::forward<Args>(args)...);
			}
			template <typename... Args>
			inline static void LogWarning(spdlog::format_string_t<Args...> fmt, Args&&... args)
			{
				if (!_logger)
					return;

				_logger->Log_Internal(spdlog::level::level_enum::warn, fmt, std::forward<Args>(args)...);
			}
			template <typename... Args>
			inline static void LogError(spdlog::format_string_t<Args...> fmt, Args&&... args)
			{
				if (!_logger)
					return;

				_logger->Log_Internal(spdlog::level::level_enum::err, fmt, std::forward<Args>(args)...);
			}
		private:
			static Logger* _logger;
	};
}

