#include "Logger.h"


Aether::Logger::Logger(std::string&& name)
{
	this->Initialize(std::move(name));
}

Aether::Logger::~Logger()
{
	this->Release();
}

void Aether::Logger::Initialize(std::string&& name)
{
	_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
	_sink->set_color_mode(spdlog::color_mode::always);
	_sink->set_color(spdlog::level::info, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	_sink->set_color(spdlog::level::warn, (FOREGROUND_RED | FOREGROUND_GREEN) | FOREGROUND_INTENSITY);
	_sink->set_color(spdlog::level::err, FOREGROUND_RED | FOREGROUND_INTENSITY);
	_logger = std::make_shared<spdlog::logger>(name, _sink);
	_logger->set_level(spdlog::level::trace);
	_logger->set_pattern("%^[%H:%M:%S] [%n]  %v %$");
}

void Aether::Logger::Release()
{
	_sink = nullptr;
	_logger = nullptr;
}