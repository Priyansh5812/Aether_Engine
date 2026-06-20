#pragma once
#ifdef AE_WINDOWS
#include <iostream>
#include "EventSystem/Delegate.h"
#include "Log/EDebug.h"
#include <memory>
using namespace Aether;
using namespace EventSystems;
extern Application* CreateApplication();

void Function_1(int value)
{
	Debug::Log("Function_1 Executed {0}" , value);
}

void Function_2()
{
	Debug::Log("Function_2 Executed");
}

class Demo
{
public:
	void CallMe(std::string str)
	{
		Debug::Log("{0}", str);
	}
};

int main()
{	
	Application* app = Aether::CreateApplication();
	Delegate<void , std::string> d;
	Demo demo;
	d.Bind<Demo , &Demo::CallMe>(&demo);
	d.Invoke("JGBkjdasbndj");
	app->Run();
	delete app;
	return 0;
}
#endif