#pragma once
#ifdef AE_WINDOWS
#include <iostream>
#include "EventSystem/Action.h"
#include <functional>
#include <chrono>
#include "Log/EDebug.h"
#include <memory>
using namespace Aether;
using namespace EventSystems;
extern Application* CreateApplication();

class Test
{
public:
	void SomeFunc()
	{
		Debug::Log("SomeFunc");
	}
};


int main()
{	
	Application* app = Aether::CreateApplication();
	Delegate<void> del;
	Test obj;
	del.Bind([&obj]() {obj.SomeFunc();});
	del.Invoke();
	app->Run();
	delete app;
	return 0;
}
#endif