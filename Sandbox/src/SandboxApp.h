#pragma once

#include <QuestEngine.h>

class SandboxApp : public Quest::Application
{
public:
	SandboxApp();
	~SandboxApp() override;
	void OnTick() override;
};