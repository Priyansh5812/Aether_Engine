#pragma once

#include "Core.h"

namespace Aether
{
	class AE_API Application
	{	
	public:
		Application();
		~Application();
		virtual void Run();
	};


	//defined in client / Sandbox
	Application* CreateApplication();
}


