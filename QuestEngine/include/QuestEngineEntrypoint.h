#ifndef QUEST_ENGINE_ENTRYPOINT_INCLUDED
#define QUEST_ENGINE_ENTRYPOINT_INCLUDED

#include "Engine/Engine.h"
#include "Core/Logger.h"



// THE ENTRYPOINT FOR THE ENGINE
// Initialize the engine systems and then create the user-defined application
int QE::gCounterTest = 0;
int main(int argc, char** argv)
{
	QE::gCounterTest = 1;
	// Initialize logger system before anything else
	QE::Logger::CreateInfo ci;
	QE::Logger::Init(ci);
	QE_CORE_DEBUG_TAG("GLOBAL", "Counter: {}", QE::gCounterTest);

	// Initialize the engine context singleton
	QE::Engine::Init();

	// Run the main loop
	QE::Engine::Get().Run();

	// Deinit static systems
	QE::Logger::Shutdown();

	// Shutdown the engine
	QE::Engine::Shutdown();

	return 0;
}

#endif // QUEST_ENGINE_ENTRYPOINT_INCLUDED