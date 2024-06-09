#pragma once

#include <QuestEngine/QuestEngine.h>

class SandboxApp : public QE::Application
{
public:
	SandboxApp();
	~SandboxApp() override;
	void OnTick() override;
};