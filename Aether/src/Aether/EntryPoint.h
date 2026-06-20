#pragma once
#ifdef AE_WINDOWS
#include <iostream>
#include "EventSystem/Action.h"
#include "Log/EDebug.h"
#include <memory>
using namespace Aether;
using namespace EventSystems;
extern Application* CreateApplication();

void Function_1()
{
	Debug::Log("Function_1 Executed {0}" , 2);
}

void Function_2()
{
	Debug::Log("Function_2 Executed");
}

class Demo
{
public:
	void CallMe(std::string value)
	{
		Debug::Log("{0} 1st", value);
	}
	void CallMe2(std::string value)
	{
		Debug::Log("{0} 2nd", value);
	}
};

int main()
{	
	Application* app = Aether::CreateApplication();
	Action<std::string> del;
	Demo d;
	del.AddListener<Demo, &Demo::CallMe>(&d);
	del.AddListener<Demo, &Demo::CallMe2>(&d);
	del.Invoke("Yay");
	Debug::Log("----------------");
	del.RemoveListener<Demo , &Demo::CallMe>(&d);
	del.Invoke("Yay");
	app->Run();
	delete app;
	return 0;
}
#endif