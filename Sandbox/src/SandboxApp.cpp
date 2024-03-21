#include "SandboxApp.h"

#include <iostream>
#include <QuestEngine.h>
// #include <Quest.h>
// #include <QuestEntrypoint.h>

// SandboxApp::SandboxApp(Quest::Application::ApplicationSpecification spec)
// 	: Quest::Application(spec), m_Specification(spec)
// {
// 	//QE_APP_INFO("Sandbox Application Constructor");
// }

// SandboxApp::~SandboxApp()
// {

// }

// Quest::ScopedPtr<Quest::Application> Quest::CreateApplication(Application::ApplicationSpecification spec) {
// 	return Quest::CreateScope<SandboxApp>(spec);
// } 

void test()
{
	std::cout << "Hello World!" << std::endl;
}

int main(int argc, char** argv)
{
	test();
	std::cout << qtest() << std::endl;
}