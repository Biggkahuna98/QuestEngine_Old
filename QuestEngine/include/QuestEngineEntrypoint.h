#pragma once

#include "Core/Application.h"
#include "Core/Assert.h"
#include "Core/Logger.h"



// THE ENTRYPOINT FOR THE ENGINE
// Initialize the engine systems and then create the user-defined application
int main(int argc, char** argv)
{
	// Initialize logger system before anything else
	Quest::Logger::Init();
	QE_CORE_ASSERT(4 == 4, "fail");

	// Create the application from the user-defined CreateApplication() in the consuming program
	std::unique_ptr<Quest::Application> app = CreateApplication();

	// Initialize engine level systems

	// Deinit static systems
	Quest::Logger::Shutdown();

	return 0;
}