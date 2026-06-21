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

void Function_2()
{	
	///	CAUTION : Uncommenting the calculatio will make the assignment overhead less visible
	//// Some Complex Calculation
	//for (size_t i = 1; i < 50; i++)
	//{
	//	float val = sqrt(i);
	//	val = fmod(val, 2.0f);
	//	val *= 10.0f;
	//}
}


void FuncBenchmark()
{	
	EDebug::Log("------------ STD:: FUNCTIONAL -------------");
	auto startTime = std::chrono::high_resolution_clock::now();
	std::vector<std::function<void()>> funcs;
	funcs.reserve(100000);
	for (int i = 0; i < funcs.capacity(); i++)
	{
		std::function<void()> fn;
		fn = Function_2;
		funcs.push_back(fn);
	}
	auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - startTime);
	EDebug::Log("Func Add Listeners Duration : {0}", duration.count());
	startTime = std::chrono::high_resolution_clock::now();
	for (auto& i : funcs)
	{
		i();
	}
	
	duration = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - startTime);
	EDebug::Log("Func Invocation Duration : {0}", duration.count());
	startTime = std::chrono::high_resolution_clock::now();
	for (auto& i : funcs)
	{
		i = nullptr;
	}
	duration = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - startTime);
	EDebug::Log("Func Remove Listeners Duration : {0}", duration.count());
}

void CustomDelegateBenchmark()
{	
	EDebug::Log("------------ ACTIONS -------------");
	auto startTime = std::chrono::high_resolution_clock::now();
	Action action(100000);
	for (int i = 0; i < 100000; i++)
	{
		action.AddListener <&Function_2 > ();
	}
	auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - startTime);
	EDebug::Log("Action Add Listeners Duration : {0}", duration.count());
	startTime = std::chrono::high_resolution_clock::now();


	action.Invoke();


	duration = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - startTime);
	EDebug::Log("Action Invocation Duration : {0}", duration.count());
	startTime = std::chrono::high_resolution_clock::now();

	action.RemoveAllListeners();


	duration = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - startTime);
	EDebug::Log("Action Clear Duration : {0}", duration.count());
}

int main()
{	
	Application* app = Aether::CreateApplication();
	FuncBenchmark();
	CustomDelegateBenchmark();
	app->Run();
	delete app;
	return 0;
}
#endif