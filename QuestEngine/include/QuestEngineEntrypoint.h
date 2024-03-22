#pragma once

#include "Core/Application.h"
#include "Core/Assert.h"



// THE ENTRYPOINT FOR THE ENGINE
// Initialize the engine systems and then create the user-defined application
int main(int argc, char** argv)
{
	// Initialize logger system before anything else
	QE_CORE_ASSERT(4 == 4, "fail");

	// Create the application from the user-defined CreateApplication() in the consuming program
	std::unique_ptr<Quest::Application> app = CreateApplication();
	app->Test();

	// Initialize engine level systems

	return 0;
}