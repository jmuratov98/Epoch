#include "Sandbox/Sandbox.h"

// --------------- Example Layer -----------------

SandboxLayer::SandboxLayer()
	: Layer("SandboxLayer")
{ }

void SandboxLayer::onUpdate()
{

}

void SandboxLayer::onEvent(Epoch::Event& e)
{
	EGE_CLIENT_TRACE(e);
}

// --------------- Example Game -----------------

Sandbox::Sandbox()
{
	pushLayer(new SandboxLayer());
}

Sandbox::~Sandbox()
{
}

// --------------- Client -----------------------

Epoch::Application* Epoch::create_application()
{
	return new Sandbox();
}
