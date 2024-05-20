// NOLINTBEGIN
#include "SandboxApp.h"

#include <QuestEngine.h>
#include <QuestEngineEntrypoint.h>

#include <iostream>
#include <memory>

SandboxApp::SandboxApp() : Quest::Application()
{
	QE_TRACE_TAG("Sandbox", "App Constructor");
}

SandboxApp::~SandboxApp()
{
}

void SandboxApp::OnTick()
{

}

std::unique_ptr<Quest::Application> CreateApplication() 
{ 
	return std::make_unique<SandboxApp>(); 
}

// NOLINTEND