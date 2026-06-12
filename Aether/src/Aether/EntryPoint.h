#pragma once
#pragma once
#include <iostream>
#ifdef AE_WINDOWS
extern Aether::Application* Aether::CreateApplication();

int main()
{	
	std::cout << "Aether Engine Started !!!" << std::endl;
	Aether::Application* app = Aether::CreateApplication();
	app->Run();
	delete app;
	return 0;
}
#endif