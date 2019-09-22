#pragma once

#include <Epoch.h>

class SandboxLayer : public Epoch::Layer
{
public:
	SandboxLayer();

	virtual void onUpdate(Epoch::Timestep timestep) override;
	virtual void onEvent(Epoch::Event& e) override;
	virtual void onImGuiRender() override;

private:
	std::shared_ptr<Epoch::Shader> m_FlatColorShader;
	std::shared_ptr<Epoch::VertexArray> m_BlueSquareVAO;

	Epoch::OrthographicCameraController m_CameraController;
};

class Sandbox : public Epoch::Application
{
public:
	Sandbox();
	~Sandbox();
};