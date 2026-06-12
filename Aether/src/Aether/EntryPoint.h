#pragma once
#ifdef AE_WINDOWS
#include <iostream>
#include "EDebug.h"
#include <memory>
//#include "Debug.h"
using namespace Aether;
extern Application* CreateApplication();

int main()
{	
	Debug::Init();
	Debug::Log("Test Log");
	Debug::LogWarning("Test Warning");
	Debug::LogError("Test Error");
	EDebug::Init();
	EDebug::Log("Test Log");
	EDebug::LogWarning("Test Warning");
	EDebug::LogError("Test Error");
	Application* app = Aether::CreateApplication();
	app->Run();
	Debug::Dispose();
	EDebug::Dispose();
	delete app;
	return 0;
}
#endif