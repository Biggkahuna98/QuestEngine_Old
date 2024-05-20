#ifndef QUEST_ENGINE_ENTRYPOINT_INCLUDED
#define QUEST_ENGINE_ENTRYPOINT_INCLUDED

#include "Engine/Engine.h"
#include "Core/Logger.h"



// THE ENTRYPOINT FOR THE ENGINE
// Initialize the engine systems and then create the user-defined application
int Quest::gCounterTest = 0;
int main(int argc, char** argv)
{
	Quest::gCounterTest = 1;
	// Initialize logger system before anything else
	Quest::Logger::CreateInfo ci;
	Quest::Logger::Init(ci);
	QE_CORE_DEBUG_TAG("GLOBAL", "Counter: {}", Quest::gCounterTest);

	// Initialize the engine context singleton
	Quest::Engine::Init();

	// Run the main loop
	Quest::Engine::Get().Run();

	// Deinit static systems
	Quest::Logger::Shutdown();

	// Shutdown the engine
	Quest::Engine::Shutdown();

	return 0;
}

#endif // QUEST_ENGINE_ENTRYPOINT_INCLUDED