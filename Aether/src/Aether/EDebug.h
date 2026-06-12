#pragma once
#include "LogBase.h"
#include <memory>
namespace Aether
{
	class EDebug : public LogBase
	{
		public:
			static void Init();
			template<typename... Args>
			inline static void Log(spdlog::format_string_t<Args...> fmt, Args&&... args)
			{
				if (!isInitialized)
					return;

				_logger->info(fmt, std::forward<Args>(args)...);
			};
			static void Dispose();
	};
}

