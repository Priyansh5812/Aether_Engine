#include "Application.h"
#include "Log/Debug.h"
#include "Log/EDebug.h"
namespace Aether
{
	Application::Application()
	{
		EDebug::Init();
		Debug::Init();
	}
	Application::~Application()
	{
		Debug::Dispose();
		EDebug::Dispose();
	}

	void Application::Run()
	{
		while (1);
	}
}
