// NOLINTBEGIN
#include "SandboxApp.h"

#include <QuestEngine/QuestEngine.h>
#include <QuestEngine/QuestEngineEntrypoint.h>

#include <iostream>
#include <memory>

SandboxApp::SandboxApp() : QE::Application()
{
	QE_TRACE_TAG("Sandbox", "App Constructor");
}

SandboxApp::~SandboxApp()
{
}

void SandboxApp::OnTick()
{

}

std::unique_ptr<QE::Application> CreateApplication() 
{ 
	return std::make_unique<SandboxApp>(); 
}

// NOLINTEND