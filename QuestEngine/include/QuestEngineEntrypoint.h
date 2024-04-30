#ifndef QUEST_ENGINE_ENTRYPOINT_INCLUDE
#define QUEST_ENGINE_ENTRYPOINT_INCLUDE

#include "Core/Application.h"
#include "Core/Logger.h"



// THE ENTRYPOINT FOR THE ENGINE
// Initialize the engine systems and then create the user-defined application
int main(int argc, char** argv)
{
	// Initialize logger system before anything else
	Quest::Logger::CreateInfo ci;
	Quest::Logger::Init(ci);

	// Create the application from the user-defined CreateApplication() in the consuming program
	std::unique_ptr<Quest::Application> app = CreateApplication();

	// Initialize engine level systems

	// Deinit static systems
	Quest::Logger::Shutdown();

	return 0;
}

#endif // QUEST_ENGINE_ENTRYPOINT_INCLUDE