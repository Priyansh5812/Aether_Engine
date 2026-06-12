#pragma once
#ifdef AE_WINDOWS
#include "EDebug.h"
#include <iostream>
extern Aether::Application* Aether::CreateApplication();

int main()
{	
	Aether::EDebug::Init();
	Aether::EDebug::Log("Logging Engine");
	std::cout << "Aether Engine Started !!!" << std::endl;
	Aether::Application* app = Aether::CreateApplication();
	
	app->Run();
	Aether::EDebug::Dispose();
	delete app;
	return 0;
}
#endif