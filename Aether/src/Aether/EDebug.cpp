#include "EDebug.h"

Aether::Logger* Aether::EDebug::_logger = nullptr;


void Aether::EDebug::Init()
{
	if (_logger)
	{
		LogWarning("Logger Reinitialization attempted!!!");
		return;
	}
	_logger = new Logger(std::string("Core"));
}

void Aether::EDebug::Dispose()
{
	if (!_logger)
	{
		return;
	}

	LogWarning("Logger Disposed");
	delete _logger;
}