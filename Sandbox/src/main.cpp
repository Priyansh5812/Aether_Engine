#pragma once
#include <Aether.h>
#include <iostream>
class Sandbox : public Aether::Application 
{	

};

Aether::Application* Aether::CreateApplication()
{	
	return new Sandbox();
}