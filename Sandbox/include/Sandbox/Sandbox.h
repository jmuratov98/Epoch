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
	Epoch::ShaderLibrary m_ShaderLibrary;
	Epoch::Ref<Epoch::Shader> m_FlatColorShader;
	Epoch::Ref<Epoch::VertexArray> m_FlatSquareVAO;
	Epoch::Ref<Epoch::Texture2D> m_CheckerboardTexture;

	glm::vec3 m_SquareColor = { 0.2, 0.3, 0.8 };

	Epoch::OrthographicCameraController m_CameraController;
};

class Sandbox : public Epoch::Application
{
public:
	Sandbox();
	~Sandbox();
};