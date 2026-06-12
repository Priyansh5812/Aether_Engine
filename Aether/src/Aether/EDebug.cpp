#include "EDebug.h"


	std::shared_ptr<spdlog::logger>Aether::LogBase::_logger = nullptr;
	bool Aether::LogBase::isInitialized = false;


	void Aether::EDebug::Init()
	{
		if (LogBase::isInitialized)
		{
			LogBase::_logger->info("Engine Logger Already Initialized...");
			return;
		}

		LogBase::_logger = spdlog::stderr_color_mt("CORE");
		LogBase::isInitialized = !(LogBase::_logger == nullptr);
		LogBase::_logger->set_pattern("[%H:%M:%S] [%s : %#] %v");
		LogBase::_logger->info("Logger Successfully Initialized !!!");
	}
	
	void Aether::EDebug::Dispose()
	{
		LogBase::isInitialized = (bool)(LogBase::_logger = nullptr);
	}

