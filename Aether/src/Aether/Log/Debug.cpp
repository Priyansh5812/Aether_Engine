#include "Debug.h"


Aether::Logger* Aether::Debug::_logger = nullptr;


void Aether::Debug::Init()
{
	if (_logger)
	{	
		LogWarning("Logger Reinitialization attempted!!!");
		return;
	}

	_logger = new Logger(std::string("Client"));
	Log("Initialized");
}



void Aether::Debug::Dispose()
{
	if (!_logger)
	{
		return;
	}

	LogWarning("Logger Disposed");
	delete _logger;
}