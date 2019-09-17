#include "Sandbox/Sandbox.h"

#include <imgui.h>

// --------------- Example Layer -----------------

SandboxLayer::SandboxLayer()
	: Layer("SandboxLayer")
{ }

void SandboxLayer::onUpdate()
{
}

void SandboxLayer::onEvent(Epoch::Event& e)
{
	if (Epoch::Input::isKeyPressed(EGE_KEY_A))
		EGE_CORE_INFO("Key A is pressed");
}

void SandboxLayer::onImGuiRender()
{
	ImGui::Begin("Text");
	ImGui::Text("Hello, World");
	ImGui::End();
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
