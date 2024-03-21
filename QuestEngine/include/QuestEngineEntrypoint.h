#pragma once

#include "Core/Application.h"



// THE ENTRYPOINT FOR THE ENGINE
// Initialize the engine systems and then create the user-defined application
int main(int argc, char** argv)
{
	std::unique_ptr<Quest::Application> app = CreateApplication();
	app->Test();

	return 0;
}