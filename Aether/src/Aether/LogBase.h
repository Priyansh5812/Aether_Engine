#pragma once

#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "Core.h"

namespace Aether
{
	class LogBase
	{	
		protected:
			static bool isInitialized;
			static std::shared_ptr<spdlog::logger> _logger;
	};
}

