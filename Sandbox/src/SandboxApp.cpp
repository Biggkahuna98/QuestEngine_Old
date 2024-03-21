#include "SandboxApp.h"

#include <QuestEngine.h>
#include <QuestEngineEntrypoint.h>

#include <iostream>

SandboxApp::SandboxApp()
	: Quest::Application()
{
	std::cout << "SandboxApp::SandboxApp\n";
}

SandboxApp::~SandboxApp()
{
	std::cout << "SandboxApp::~SandboxApp\n";
}


std::unique_ptr<Quest::Application> CreateApplication()
{
	return std::make_unique<SandboxApp>();
}