#ifndef QUEST_ENGINE_ENTRYPOINT_INCLUDED
#define QUEST_ENGINE_ENTRYPOINT_INCLUDED

#include "Engine/QuestEngine.h"
#include "Core/Application.h"
#include "Core/Logger.h"



// THE ENTRYPOINT FOR THE ENGINE
// Initialize the engine systems and then create the user-defined application
int main(int argc, char** argv)
{
	// Initialize logger system before anything else
	Quest::Logger::CreateInfo ci;
	Quest::Logger::Init(ci);

	// Initialize the engine context singleton
	Quest::QuestEngine::Init();

	// The application exists from the QuestEngine::Init() call, so run it
	Quest::QuestEngine::Get().GetApplication().Run();

	// Deinit static systems
	Quest::Logger::Shutdown();

	// Shutdown the engine
	Quest::QuestEngine::Shutdown();

	return 0;
}

#endif // QUEST_ENGINE_ENTRYPOINT_INCLUDED