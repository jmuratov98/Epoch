#pragma once

#include <Epoch.h>

class SandboxLayer : public Epoch::Layer
{
public:
	SandboxLayer();

	virtual void onUpdate() override;
	virtual void onEvent(Epoch::Event& e) override;

};

class Sandbox : public Epoch::Application
{
public:
	Sandbox();
	~Sandbox();
};